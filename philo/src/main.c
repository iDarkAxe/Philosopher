/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:45:40 by ppontet           #+#    #+#             */
/*   Updated: 2025/03/18 14:23:01 by ppontet          ###   ########lyon.fr   */
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
	if (parse_args(argc, argv, &rules.rules) != 0)
		return (1);
	if (init_philo(&rules) != 0)
	{
		write(2, "Error:\nCreation of rules\n", 25);
		free_philo(&rules.rules, &rules.shared, rules.rules.nb_philo);
		return (1);
	}
	gettimeofday(&rules.rules.time_at_start, NULL);
	pthread_mutex_init(&rules.shared.is_printing, NULL);
	if (thread_creation(&rules.rules, &rules.shared) != 0)
		return (1);
	while (are_all_threads_dead(&rules.rules) == 0)
		usleep(10);
	free_philo(&rules.rules, &rules.shared, rules.rules.nb_philo);
	return (0);
}
