/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:47:14 by kakumar           #+#    #+#             */
/*   Updated: 2023/03/22 16:06:37 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_data *data, int i)
{
	t_philo philosopher;

	philosopher.index = i;
	philosopher.times_eaten = 0;
	philosopher.is_sleeping = 0;
	philosopher.is_eating = 0;
	philosopher.is_dead = 0;
	philosopher.data = data;
	data->philo[i] = philosopher;
}

void	init_data_philos(t_data *data, char **argv)
{
	int	i;

	i = 0;
	data->number_of_philosophers = philo_atoi(argv[1]);
	data->time_to_die = philo_atoi(argv[2]);
	data->time_to_eat = philo_atoi(argv[3]);
	data->time_to_sleep = philo_atoi(argv[4]);
	if (argv[5])
		data->number_of_times_to_eat = philo_atoi(argv[5]);
	else
		data->number_of_times_to_eat = -1;
	data->philo = malloc (sizeof(t_philo) * data->number_of_philosophers);
	while (i < data->number_of_philosophers)
	{
		init_philos(data, i);
		i++;
	}
}