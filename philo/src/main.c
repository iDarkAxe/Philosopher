/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:45:40 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/16 12:40:59 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "routine.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

static void	observer_task(t_philo *philo);
static int	thread_manip(t_rules *rules, t_shared *shared, t_philo *philo);

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
 * @brief Function to create the threads and join them
 *
 * @param rules structure of const rules
 * @param shared structure of shared variables
 * @param philo head of philosopher structure
 * @return int 0 if successful, 1 otherwise
 */
static int	thread_manip(t_rules *rules, t_shared *shared, t_philo *philo)
{
	int	count;

	count = 0;
	while (count < rules->nb_philo)
	{
		if (pthread_create(&philo[count].philosopher, NULL,
				(void *(*)(void *))start_routine, (void *)&philo[count]) != 0)
		{
			free_philos(philo);
			free_shared(shared, rules->nb_philo, 0);
			return (1);
		}
		count++;
	}
	observer_task(philo);
	count = 0;
	while (count < rules->nb_philo)
	{
		pthread_join(philo[count].philosopher, NULL);
		count++;
	}
	return (0);
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
	thread_manip(&rules, &shared, philo);
	free_philos(philo);
	free_shared(&shared, rules.nb_philo, 0);
	return (0);
}
