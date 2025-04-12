/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:45:40 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/12 13:03:01 by ppontet          ###   ########lyon.fr   */
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
		error_message(NBR_OF_ARGUMENT_INVALID);
		return (1);
	}
	if (parse_args(argc, argv, &rules.rules) != 0)
		return (1);
	if (init_philo(&rules) != 0)
	{
		error_message(RULES_NOT_CREATED);
		free_philo(&rules.rules, &rules.shared, rules.rules.nb_philo);
		return (1);
	}
	gettimeofday(&rules.rules.time_at_start, NULL);
	pthread_mutex_init(&rules.shared.is_printing, NULL);
	pthread_mutex_init(&rules.shared.read_rules, NULL);
	if (thread_creation(&rules.rules, &rules.shared) != 0)
		return (1);
	while (1)
	{
		pthread_mutex_lock(&rules.shared.read_rules);
		if (are_all_threads_dead(&rules.rules) != 0)
			break ;
		pthread_mutex_unlock(&rules.shared.read_rules);
		usleep(10);
	}
	free_philo(&rules.rules, &rules.shared, rules.rules.nb_philo);
	return (0);
}
