/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 10:28:57 by kakumar           #+#    #+#             */
/*   Updated: 2023/03/31 11:12:58 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	food_eaten(t_data *data, int i)
{
	pthread_mutex_lock(&data->common->death_status);
	data->philo[i].state = 3;
	pthread_mutex_unlock(&data->common->death_status);
	pthread_mutex_lock(&data->common->print_mute);
	pthread_mutex_destroy(&data->common->print_mute);
	free_forks(data);
}

int	death(t_data *data)
{		
	if (get_time_in_ms() - data->philo[data->i].last_meal \
	>= data->common->time_to_die)
	{
		pthread_mutex_unlock(&data->common->meal_mutex);
		usleep(100);
		data->philo[data->i].state = 3;
		pthread_mutex_lock(&data->common->print_mute);
		printf("%lli %i %s\n", get_time_in_ms() - \
		data->common->start_time, data->philo[data->i].index, "died");
		free_forks(data);
		return (1);
	}
	pthread_mutex_unlock(&data->common->death_status);
	pthread_mutex_unlock(&data->common->meal_mutex);
	return (0);
}
