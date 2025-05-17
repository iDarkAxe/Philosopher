/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:45:40 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/17 13:54:01 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "routine.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

static void	observer_task(t_philo *philo);

/**
 * @brief Function to create the observer thread
 *
 * @param philo head of philosopher structure
 */
static void	observer_task(t_philo *philo)
{
	while (is_sim_running(philo) == 1)
	{
		if (has_everyone_ate(philo) == 1)
		{
			pthread_mutex_lock(&philo->shared->mutex_is_running);
			philo->shared->is_running = 0;
			if (ALL_ATE_MSG == 1)
			{
				pthread_mutex_lock(&philo->shared->mutex_printing);
				printf("All philosophers have eaten enough\n");
				pthread_mutex_unlock(&philo->shared->mutex_printing);
			}
			pthread_mutex_unlock(&philo->shared->mutex_is_running);
			break ;
		}
		usleep(DELAY);
	}
}

/**
 * @brief Main function of the program philo
 *
 * @param argc argument count
 * @param argv array of arguments
 * @return int 0 OK, otherwise error (1)
 */
int	main(int argc, char **argv)
{
	t_rules		rules;
	t_shared	shared;
	t_philo		*philo;

	if (parse_args(argc, argv, &rules) != 0)
		return (1);
	if (init_philos(&rules, &shared, &philo) != 0)
	{
		printf("Erreur Init philos\n");
		return (2);
	}
	if (init_mutex(&shared, philo, rules.nb_philo) != 0)
	{
		printf("Erreur Init Mutex\n");
		return (3);
	}
	if (rules.nb_philo == 1)
		thread_createone(&rules, &shared, philo);
	else
		thread_create(&rules, &shared, philo);
	observer_task(philo);
	thread_join(&rules, philo);
	free_philos(philo);
	free_shared(&shared, rules.nb_philo, 0);
	return (0);
}
