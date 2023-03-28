/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:43:42 by kakumar           #+#    #+#             */
/*   Updated: 2023/03/27 15:46:03 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_common
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_forks;
	int				start_time;
	int				number_of_times_to_eat;
	pthread_mutex_t	print_mute;
}	t_common;

typedef struct s_philo
{
	int				index;
	int				times_eaten;
	long long		last_meal;
	int				state;
	pthread_mutex_t fork_l;
	pthread_mutex_t *fork_r;
	pthread_mutex_t	message;
	long long		start;
	t_common		*common;
}	t_philo;

typedef struct s_data
{
	t_philo		*philo;
	pthread_t	*threads;
	t_common	*common;
	int			number_of_philosophers;
	int			i;
	long long	start_time;
}	t_data;

//threads
int			run_threads(t_data *data);
//initialize
void		init_data_philos(t_data *data, char **argv, t_common *common);
//utils
int			philo_atoi(char *str);
long long	get_time_in_ms(void);
void		s_leep(t_philo *philo, int time_to);
void		print_action(char *str, t_philo *philo);
#endif