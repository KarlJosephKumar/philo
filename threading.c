/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:33:42 by kakumar           #+#    #+#             */
/*   Updated: 2023/03/29 15:46:49 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void sleeping(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->state != 3)
		print_action("is sleeping", philo);
	s_leep(philo, philo->common->time_to_eat);
}

void	eat(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philo->fork_l);
	if (philo->state != 3)
		print_action("has taken a fork", philo);
	pthread_mutex_lock(philo->fork_r);
	if (philo->state != 3)
	{
		print_action("has taken a fork", philo);
		print_action("is eating", philo);
	}
	philo->last_meal = get_time_in_ms();
	philo->times_eaten++;
	if (philo->times_eaten >= philo->common->number_of_times_to_eat)
		philo->common->philos_eaten++;
	s_leep(philo, philo->common->time_to_eat);
	pthread_mutex_unlock(&philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
}

void	*routine(void *args)
{
	t_philo *philo;

	philo = (t_philo *) args;
	if ((philo->index % 2) == 1)
		usleep(philo->common->time_to_sleep * 500 / 2);
	while(1 && philo->state != 3)
	{
		eat(philo);
		sleeping(philo);
		if (philo->state != 3)
			print_action("is thinking", philo);
	}
	return (NULL);
}

void	monitoring(void *args)
{
	t_data	*data;
	int		i;
	int		flag;

	data = args;
	i = 0;
	flag = 0;
	while(1 && flag != 1)
	{
		if (i >= data->number_of_philosophers)
			i = 0;
		if (data->common->philos_eaten >= data->common->number_of_times_to_eat)
		{
			data->philo[i].state = 3;
			pthread_mutex_lock(&data->common->print_mute);
			pthread_mutex_destroy(&data->common->print_mute);
			// free_forks(data);
			return ;
		}
		if ((get_time_in_ms() - data->philo[i].last_meal) >= data->common->time_to_die)
		{
			usleep(100);
			flag = 1;
			pthread_mutex_lock(&data->common->print_mute);
			// data->philo[i].state = 3;
			printf("%lli %i %s\n", get_time_in_ms() - data->common->start_time, data->philo[i].index, "died");
			pthread_mutex_unlock(&data->common->print_mute);
			// free_forks(data);
			return ;
		}
		usleep(500);
		i++;
	}
	return ;
}

int	run_threads(t_data *data)
{
	int	j;

	data->i = 0;
	data->common->start_time = get_time_in_ms();
	while (data->i < data->number_of_philosophers)
	{
		data->philo[data->i].last_meal = data->common->start_time;
		print_action("is thinking", &data->philo[data->i]);
		if (pthread_create(&data->threads[data->i], NULL, &routine, &data->philo[data->i]) != 0)
		{
			printf("Thread creation failure\n");
			return (-1);
		}
		data->i++;
	}
	monitoring(data);
	j = 0;
	while (j < data->number_of_philosophers && data->number_of_philosophers > 1)
	{
		if (pthread_join(data->threads[j], NULL) != 0)
			return (-1);
		j++;
	}
	return (0);
}
