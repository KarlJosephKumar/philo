/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:33:42 by kakumar           #+#    #+#             */
/*   Updated: 2023/03/27 14:14:21 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void sleeping(t_philo *philo)
{
	int	i;

	i = 0;
	printf("%lld id: %i philo is sleeping\n", get_time_in_ms() - philo->start, philo->index);
	philo->state = 2;
	while (i < 1000)
	{
		usleep(philo->common->time_to_sleep);
		i++;
	}
}

void	eat(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philo->fork_l);
	philo->forks = 1;
	printf("%lld id: %i philo is holding fork L\n", get_time_in_ms() - philo->start, philo->index);
	pthread_mutex_lock(philo->fork_r);
	philo->forks = 2;
	printf("%lld id: %i philo is holding fork R\n", get_time_in_ms() - philo->start, philo->index);
	printf("%lli id: %i philo is eating\n", get_time_in_ms() - philo->start, philo->index);
	philo->last_meal = get_time_in_ms() - philo->start;
	philo->state = 1;
	philo->times_eaten++;
	while (i < 1000)
	{
		usleep(philo->common->time_to_eat);
		i++;
	}
	pthread_mutex_unlock(&philo->fork_l);
	philo->forks = 1;
	pthread_mutex_unlock(philo->fork_r);
	philo->forks = 0;
}
// void think();

void	*routine(void *args)
{
	t_philo *philo;

	philo = (t_philo *) args;
	if ((philo->index % 2) == 1)
		usleep(10);
	while(1)
	{
		philo->state = 0;
		printf("%lld id: %i philo is thinking\n", get_time_in_ms() - philo->start, philo->index);
		eat(philo);
		sleeping(philo);
	}
	return (NULL);
}

int	run_threads(t_data *data)
{
	data->common->start_time = get_time_in_ms();
	while (data->i < data->number_of_philosophers)
	{
		data->philo[data->i].start = get_time_in_ms();
		if (pthread_create(&data->threads[data->i], NULL, &routine, &data->philo[data->i]) != 0)
		{
			printf("Thread creation failure\n");
			return (-1);
		}
		data->i++;
	}
	while (1)
		usleep(10);
	return (0);
}
