/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:47:14 by kakumar           #+#    #+#             */
/*   Updated: 2023/03/23 14:46:05 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_data *data, int i, t_common *common)
{
	t_philo philosopher;

	philosopher.index = i;
	philosopher.times_eaten = 0;
	philosopher.last_meal = 0;
	philosopher.state = 0;
	philosopher.common = common;
	philosopher.start_time = get_time_in_ms();
	pthread_mutex_init(&philosopher.fork, NULL);
	data->philo[i] = philosopher;
}

void	init_data_philos(t_data *data, char **argv, t_common *common)
{
	int	i;

	i = 0;
	data->number_of_philosophers = philo_atoi(argv[1]);
	common->time_to_die = philo_atoi(argv[2]);
	common->time_to_eat = philo_atoi(argv[3]);
	common->time_to_sleep = philo_atoi(argv[4]);
	data->common = common;
	if (argv[5])
		common->number_of_times_to_eat = philo_atoi(argv[5]);
	else
		common->number_of_times_to_eat = -1;
	data->philo = malloc (sizeof(t_philo) * data->number_of_philosophers);
	while (i < data->number_of_philosophers)
	{
		init_philos(data, i, common);
		i++;
	}
	data->threads = malloc (sizeof(pthread_t) * data->number_of_philosophers);
}