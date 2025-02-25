/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:45:40 by ppontet           #+#    #+#             */
/*   Updated: 2025/02/25 10:47:04 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Main function of the program philo
 * 
 * @param argc argument count
 * @param argv array of arguments
 * @return int 0 OK, otherwise error (1)
 */
int	main(int argc, char **argv)
{
	t_rules	rules;

	if (argc < 5 || argc > 6)
	{
		write(2, "Error:\nWrong number of arguments\n", 33);
		return (1);
	}
	if (parse_args(argc, argv, &rules) != 0)
		return (1);
	if (init_philo(&rules) != 0)
	{
		write(2, "Error:\nCreation of rules\n", 25);
		free_philo(&rules, rules.nb_philo);
		return (1);
	}
	gettimeofday(&rules.time_at_start, NULL);
	pthread_mutex_init(&rules.is_printing, NULL);
	if (thread_creation(&rules) != 0)
		return (1);
	while (are_all_threads_dead(&rules) == 0)
		usleep(10);
	free_philo(&rules, rules.nb_philo);
	return (0);
}
