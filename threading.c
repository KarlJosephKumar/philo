/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:33:42 by kakumar           #+#    #+#             */
/*   Updated: 2023/03/27 15:56:38 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void sleeping(t_philo *philo)
{
	int	i;

	i = 0;
	print_action("is sleeping", philo);
	philo->state = 2;
	s_leep(philo, philo->common->time_to_eat);
}

void	eat(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philo->fork_l);
	print_action("is holding fork", philo);
	pthread_mutex_lock(philo->fork_r);
	print_action("is holding fork", philo);
	print_action("is eating", philo);
	philo->last_meal = get_time_in_ms() - philo->last_meal;
	philo->state = 1;
	philo->times_eaten++;
	s_leep(philo, philo->common->time_to_eat);
	pthread_mutex_unlock(&philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
}

void	*routine(void *args)
{
	t_philo *philo;

	philo = (t_philo *) args;
	print_action("is thinking", philo);
	if ((philo->index % 2) == 1)
		usleep(philo->common->time_to_sleep * 1000 / 2);
	while(1)
	{
		if (philo->common->number_of_times_to_eat == philo->times_eaten)
			return (NULL);
		print_action("is thinking", philo);
		philo->state = 0;
		eat(philo);
		sleeping(philo);
	}
	return (NULL);
}

// Do thread join, do monitoring;;


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
