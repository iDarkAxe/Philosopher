/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:45:40 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/13 17:27:32 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int		thread_manip(t_const_rules *rules, t_shared *shared, t_philo *philo);
void	waits_for_equals(pthread_mutex_t *mutex, const int *const value1,
			const int *const value2);
void	philo_routine(void *arg);

void	waits_for_equals(pthread_mutex_t *mutex, const int *const value1,
		const int *const value2)
{
	while (1)
	{
		pthread_mutex_lock(mutex);
		if (*value1 == *value2)
		{
			pthread_mutex_unlock(mutex);
			return ;
		}
		pthread_mutex_unlock(mutex);
		usleep(10);
	}
}

void	philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (arg == NULL)
		return ;
	philo->state = 1;
	pthread_mutex_lock(&philo->shared->read_shared);
	philo->shared->ready++;
	pthread_mutex_unlock(&philo->shared->read_shared);
	waits_for_equals(&philo->shared->read_shared, &philo->shared->ready,
		&philo->const_rules->nb_philo);
	pthread_mutex_lock(&philo->shared->print);
	printf("philo %d\n", philo->id);
	pthread_mutex_unlock(&philo->shared->print);
}

int	thread_manip(t_const_rules *rules, t_shared *shared, t_philo *philo)
{
	int	count;

	count = 0;
	while (count < rules->nb_philo)
	{
		if (pthread_create(&philo[count].philosopher, NULL,
				(void *(*)(void *))philo_routine, (void *)&philo[count]) != 0)
		{
			free_philos(philo, rules->nb_philo);
			free_shared(shared, rules->nb_philo, 0);
			return (1);
		}
		count++;
	}
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
	t_const_rules	rules;
	t_shared		shared;
	t_philo			*philo;

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
	free_philos(philo, rules.nb_philo);
	free_shared(&shared, rules.nb_philo, 0);
	return (0);
}
