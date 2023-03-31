/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:47:14 by kakumar           #+#    #+#             */
/*   Updated: 2023/03/31 10:16:40 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_l_forks(t_data *data, int i)
{
	if (i + 1 == data->number_of_philosophers)
		data->philo[i].fork_r = &data->philo[0].fork_l;
	else
		data->philo[i].fork_r = &data->philo[i + 1].fork_l;
}

void	init_common(t_data *data, t_common *common, char **argv)
{
	common->num_of_forks = philo_atoi(argv[1]);
	common->time_to_die = philo_atoi(argv[2]);
	common->time_to_eat = philo_atoi(argv[3]);
	common->time_to_sleep = philo_atoi(argv[4]);
	data->common = common;
	data->common->start_time = 0;
	data->common->philos_eaten = 0;
	pthread_mutex_init(&common->meal_mutex, NULL);
	pthread_mutex_init(&common->death_status, NULL);
	pthread_mutex_init(&common->print_mute, NULL);
}

void	init_philos(t_data *data, int i, t_common *common)
{
	t_philo	philosopher;

	philosopher.index = i;
	philosopher.times_eaten = 0;
	philosopher.state = 0;
	philosopher.common = common;
	pthread_mutex_init(&philosopher.fork_l, NULL);
	data->philo[i] = philosopher;
}

void	init_data_philos(t_data *data, char **argv, t_common *common, int argc)
{
	int	i;

	i = 0;
	data->number_of_philosophers = philo_atoi(argv[1]);
	init_common(data, common, argv);
	data->i = 0;
	if (argc == 6)
		common->number_of_times_to_eat = philo_atoi(argv[5]);
	else
		common->number_of_times_to_eat = 2147483647;
	data->philo = malloc (sizeof(t_philo) * data->number_of_philosophers);
	while (i < data->number_of_philosophers)
	{
		init_philos(data, i, common);
		i++;
	}
	i = 0;
	while (i < data->number_of_philosophers)
	{
		init_l_forks(data, i);
		i++;
	}
	data->threads = malloc (sizeof(pthread_t) * data->number_of_philosophers);
}
