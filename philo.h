/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:43:42 by kakumar           #+#    #+#             */
/*   Updated: 2023/03/22 16:05:53 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>

typedef struct s_philo
{
	int		index;
	int		times_eaten;
	int		is_sleeping;
	int		is_eating;
	int		is_dead;
	t_data *data;
}	t_philo;

typedef struct s_data
{
	t_philo	*philo;
	int		number_of_philosophers;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		number_of_times_to_eat;
}	t_data;

//initialize
void	init_data_philos(t_data *data, char **argv);
//utils
int		philo_atoi(char *str);
#endif