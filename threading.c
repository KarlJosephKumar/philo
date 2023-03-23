/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:33:42 by kakumar           #+#    #+#             */
/*   Updated: 2023/03/23 15:03:55 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_sleep_think_repeat(t_philo *philo)
{
	philo->start_time = philo_start_time(philo);
	printf("%lld %i philo is holding fork\n", philo->start_time, philo->index);
}

int	run_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&data->threads[i], NULL, (void *)eat_sleep_think_repeat, &data->philo[i]) == 0)
		{
			usleep(500);
		}
		else
		{
			printf("Thread creation failure\n");
			return (-1);
		}
		i++;
	}
	return (0);
}