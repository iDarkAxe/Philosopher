/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:45:40 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/16 15:19:43 by ppontet          ###   ########lyon.fr   */
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
	while (is_running(philo) == 1)
	{
		if (has_everyone_ate(philo) == 1)
		{
			pthread_mutex_lock(&philo->shared->is_running_access);
			philo->shared->is_running = 0;
			if (ALL_ATE_MSG == 1)
			{
				pthread_mutex_lock(&philo->shared->print);
				printf("All philosophers have eaten enough\n");
				pthread_mutex_unlock(&philo->shared->print);
			}
			pthread_mutex_unlock(&philo->shared->is_running_access);
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
