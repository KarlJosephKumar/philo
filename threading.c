/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:33:42 by kakumar           #+#    #+#             */
/*   Updated: 2023/03/31 11:13:21 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philo->common->death_status);
	print_action("is sleeping", philo);
	pthread_mutex_unlock(&philo->common->death_status);
	s_leep(philo, philo->common->time_to_eat);
}

void	eat(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philo->fork_l);
	pthread_mutex_lock(&philo->common->death_status);
	print_action("has taken a fork", philo);
	pthread_mutex_unlock(&philo->common->death_status);
	pthread_mutex_lock(philo->fork_r);
	pthread_mutex_lock(&philo->common->death_status);
	print_action("has taken a fork", philo);
	pthread_mutex_unlock(&philo->common->death_status);
	pthread_mutex_lock(&philo->common->meal_mutex);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->common->meal_mutex);
	pthread_mutex_lock(&philo->common->death_status);
	print_action("is eating", philo);
	pthread_mutex_unlock(&philo->common->death_status);
	philo->times_eaten++;
	if (philo->times_eaten >= philo->common->number_of_times_to_eat)
		philo->common->philos_eaten++;
	s_leep(philo, philo->common->time_to_eat);
	pthread_mutex_unlock(&philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
}

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *) args;
	if ((philo->index % 2) == 1)
		usleep(philo->common->time_to_sleep * 500 / 2);
	while (1)
	{
		pthread_mutex_lock(&philo->common->death_status);
		if (philo->state != 3)
		{
			pthread_mutex_unlock(&philo->common->death_status);
			eat(philo);
			sleeping(philo);
			pthread_mutex_lock(&philo->common->death_status);
			print_action("is thinking", philo);
			pthread_mutex_unlock(&philo->common->death_status);
		}
		else
		{
			pthread_mutex_unlock(&philo->common->death_status);
			break ;
		}
	}
	return (NULL);
}

void	monitoring(void *args)
{
	t_data	*data;
	int		flag;

	data = args;
	flag = 0;
	while (1 && flag != 1)
	{
		if (data->i >= data->number_of_philosophers)
			data->i = 0;
		if (data->common->philos_eaten >= data->common->number_of_times_to_eat)
		{
			food_eaten(data, data->i);
			return ;
		}
		pthread_mutex_lock(&data->common->meal_mutex);
		pthread_mutex_lock(&data->common->death_status);
		flag = death(data);
		usleep(500);
		data->i++;
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
		if (pthread_create(&data->threads[data->i], \
		NULL, &routine, &data->philo[data->i]) != 0)
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
