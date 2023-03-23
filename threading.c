/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:33:42 by kakumar           #+#    #+#             */
/*   Updated: 2023/03/23 14:25:47 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_sleep_think_repeat(t_philo *philo)
{
	printf("%i philo is holding fork\n", philo->index);
}

void	run_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&data->threads[i], NULL, (void *)eat_sleep_think_repeat, &data->philo[i]) != 0)
		{
			printf("Thread creation failure\n");
			return ;
		}
		i++;
	}
}