/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 17:56:02 by ppontet           #+#    #+#             */
/*   Updated: 2025/03/18 15:02:53 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

static int	init_philos(t_const_rules *rules, t_shared_ressources *shared);
static void	print_message(t_philo *philo, struct timeval *time,
				enum e_living_state state);

/**
 * @brief Routine for the philosopher
 *
 * @param arg pointer to the philosopher structure
 * @return void*
 */
void	*philo_routine(void *arg)
{
	t_philo			*philo;
	struct timeval	time_day;
	struct timeval	time_delta;
	struct timeval	time_now;

	philo = (t_philo *)arg;
	if (philo == NULL)
		return (NULL);
	philo->living_state = LIVING;
	(void)time_now;
	while (philo->rules->is_everyone_ready != philo->rules->nb_philo
		&& are_all_threads_state(philo->rules, LIVING) == 0)
		usleep(10);
	gettimeofday(&philo->time_at_wakeup, NULL);
	while (philo->living_state != DIED)
	{
		philo->living_state = LIVING;
		gettimeofday(&time_day, NULL);
		// usleep(10000 * 9);
		gettimeofday(&time_delta, NULL);
		time_delta = getdeltatime(time_day);
		if (philo->rules->time_to_die <= ((time_delta.tv_sec * 1000) + (time_delta.tv_usec / 1000)))
		{
			print_message(philo, &time_day, DIED);
			return (philo);
		}
		print_message(philo, &time_day, TAKE_FORK);
		// After eating
		print_message(philo, &time_day, SLEEPING);
		usleep(philo->rules->time_to_sleep * 1000);
	}
	// print_message(philo, &time_day, TAKE_FORK);
	print_message(philo, &time_day, TAKE_FORK);
	// print_message(philo, &time_day, SLEEPING);
	// print_message(philo, &time_day, THINKING);
	// usleep(10000);
	// print_message(philo, &time_day, DIED);
	philo->living_state = DIED;
	return (philo);
}

/**
 * @brief Print message for the state of the philosopher
 *
 * @param philo philosopher
 * @param time time
 * @param state state to print
 */
static void	print_message(t_philo *philo, struct timeval *time,
		enum e_living_state state)
{
	pthread_mutex_lock(&philo->shared->is_printing);
	gettimeofday(time, NULL);
	printf("%ld %d", (time->tv_sec * 1000) + (time->tv_usec / 1000), philo->id);
	philo->living_state = state;
	if (state == NOT_STARTED)
		printf(" is not started");
	else if (state == LIVING)
		printf(" is living");
	else if (state == DIED)
		printf(" died");
	else if (state == TAKE_FORK)
		printf(" has taken a fork");
	else if (state == SLEEPING)
		printf(" is sleeping");
	else if (state == THINKING)
		printf(" is thinking");
	printf("\n");
	pthread_mutex_unlock(&philo->shared->is_printing);
}

/**
 * @brief Initialize the rules and allocates the philosophers
 *
 * @param rules rules of the program
 * @return int 0 OK, otherwise error (1)
 */
int	init_philo(t_rules *rules)
{
	rules->shared.forks = NULL;
	rules->rules.philo = ft_calloc(sizeof(t_philo),
			(size_t)rules->rules.nb_philo);
	if (rules->rules.philo == NULL)
		return (1);
	rules->shared.forks = malloc(sizeof(pthread_mutex_t)
			* (unsigned int)rules->rules.nb_philo);
	if (rules->shared.forks == NULL)
		return (1);
	rules->rules.is_everyone_ready = 0;
	if (init_philos(&rules->rules, &rules->shared) != 0)
		return (1);
	return (0);
}

/**
 * @brief Iterate over all the philosophers
 *
 * @param rules rules of the program
 * @return int 0 OK, otherwise error (1)
 */
static int	init_philos(t_const_rules *rules, t_shared_ressources *shared)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		rules->philo[i].id = i;
		rules->philo[i].nb_eat = rules->nb_eat;
		rules->philo[i].rules = rules;
		rules->philo[i].shared = shared;
		rules->philo[i].living_state = NOT_STARTED;
		if (pthread_mutex_init(&shared->forks[i], NULL) != 0)
		{
			free_philo(rules, shared, i);
			return (1);
		}
		i++;
	}
	return (0);
}

/**
 * @brief Free all the philos that were created with their forks
 *
 * @param rules rules of the program
 * @param count number of forks initialzied
 * @return int 0 OK, otherwise error (1)
 */
int	free_philo(t_const_rules *rules, t_shared_ressources *shared, int count)
{
	int	i;

	if (rules->philo != NULL)
	{
		free((void *)rules->philo);
		rules->philo = NULL;
	}
	i = 0;
	while (shared->forks != NULL && i < count)
	{
		pthread_mutex_destroy(&shared->forks[i]);
		i++;
	}
	if (shared->forks != NULL)
	{
		free((void *)shared->forks);
		shared->forks = NULL;
	}
	return (0);
}
