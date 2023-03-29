/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:12:05 by kakumar           #+#    #+#             */
/*   Updated: 2023/03/29 13:57:13 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_error(char **argv)
{
	if (philo_atoi(argv[1]) < 0)
	{
		printf("Needs to have 1 or more philosophers.\n");
		return (-1);
	}
	if (philo_atoi(argv[2]) < 1 || philo_atoi(argv[3]) < 1 || philo_atoi(argv[4]) < 1)
	{
		printf("Check the times that you have given.\n");
		return (-1);
	}
	if (argv[5])
	{
		if (philo_atoi(argv[5]) < 1)
		{
			printf("Either let them run infinitely or give them some times to eat\n");
			return (-1);
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_common	common;

	if (argc != 5 && argc != 6)
	{
		printf("Argument count error\n");
		return (-1);
	}
	if (check_error(argv) < 0)
	{
		printf("Errors found in data given in the arguments.\n");
		return (-1);
	}
	init_data_philos(&data, argv, &common, argc);
	if (run_threads(&data) == -1)
	{
		printf("Failure in run threads\n");
		return (-1);
	}
	else
	{
		free(data.philo);
		free(data.threads);
		return (0);
	}
	return 0;
}