/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:29:12 by kakumar           #+#    #+#             */
/*   Updated: 2023/03/27 15:48:06 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long get_time_in_ms(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	s_leep(t_philo *philo, int time_to)
{
	long long	end_time;

	end_time = get_time_in_ms() + time_to;
	while(end_time >= get_time_in_ms())
		usleep(500);
}
	// printf("time: %lli\n", time);

void	print_action(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->common->print_mute);
	printf("%lli %i %s\n", get_time_in_ms() - philo->start, philo->index, str);
	pthread_mutex_unlock(&philo->common->print_mute);
}

int	philo_atoi(char *str)
{
	int	sum;
	int	sign;
	int	found;

	sum = 0;
	sign = 1;
	found = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str && found)
	{
		if (*str >= '0' && *str <= '9')
			sum = sum * 10 + *str - '0';
		else
			found = 0;
		str++;
	}
	return (sign * sum);
}