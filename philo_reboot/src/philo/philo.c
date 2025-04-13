/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 17:56:02 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/13 17:22:01 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

static int	init_philos(t_const_rules *rules, t_shared *shared);
static void	print_message(t_philo *philo, struct timeval *time,
				enum e_living_state state);

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
	rules->rules.philo = ft_calloc((size_t)rules->rules.nb_philo,
			sizeof(t_philo));
	if (rules->rules.philo == NULL)
		return (1);
	rules->shared.forks = ft_calloc(sizeof(pthread_mutex_t),
			(unsigned int)rules->rules.nb_philo);
	if (rules->shared.forks == NULL)
		return (1);
	rules->rules.is_everyone_ready = 0;
	if (init_philos(&rules->rules, &rules->shared) != 0)
		return (2);
	return (0);
}

/**
 * @brief Iterate over all the philosophers
 *
 * @param rules rules of the program
 * @return int 0 OK, otherwise error (1)
 */
static int	init_philos(t_const_rules *rules, t_shared *shared)
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
