/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:03:57 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/31 12:19:10 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

static int	init_forks(t_shared *shared, t_philo *philo, int count);
static int	init_philos(t_rules *rules, t_shared *shared, t_philo **philo);
static int	init_forks_mutex(t_shared *shared, int count);
static int	init_mutex(t_shared *shared, t_philo *philo, int count);

int	init_fx(t_rules *rules, t_shared *shared, t_philo **philo)
{
	if (init_philos(rules, shared, philo) != 0)
	{
		write(2, "Erreur Init philos\n", 20);
		return (2);
	}
	if (init_mutex(shared, *philo, rules->nb_philo) != 0)
	{
		write(2, "Erreur Init Mutex\n", 19);
		return (3);
	}
	if (init_forks(shared, *philo, rules->nb_philo) != 0)
	{
		write(2, "Erreur Init Mutex\n", 19);
		return (3);
	}
	return (0);
}

/**
 * @brief Initialize the philosophers
 *
 * @param rules structure of const rules
 * @param shared structure of shared variables
 * @param philo head of philosopher structure
 * @return int
 */
int	init_philos(t_rules *rules, t_shared *shared, t_philo **philo)
{
	int	count;

	if (!rules || !shared || !philo)
		return (1);
	*philo = ft_calloc(sizeof(t_philo), (size_t)rules->nb_philo);
	if (*philo == NULL)
		return (1);
	count = 0;
	shared->ready = 0;
	while (count < rules->nb_philo)
	{
		(*philo)[count].id = count;
		(*philo)[count].shared = shared;
		(*philo)[count].rules = rules;
		count++;
	}
	shared->is_running = 1;
	return (0);
}

/**
 * @brief Initialize and allocates the forks and mutex
 *
 * @param shared structure of shared variables
 * @param count number of element
 * @return int
 */
static int	init_forks_mutex(t_shared *shared, int count)
{
	if (pthread_mutex_init(&shared->mutex_printing, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&shared->mutex_ready, NULL) != 0)
		return (2);
	shared->is_fork_taken = NULL;
	shared->forks = ft_calloc(sizeof(pthread_mutex_t), (size_t)count);
	if (shared->forks == NULL)
		return (3);
	shared->is_fork_taken = ft_calloc(sizeof(char), (size_t)count);
	if (shared->is_fork_taken == NULL)
		return (4);
	if (pthread_mutex_init(&shared->mutex_is_running, NULL) != 0)
		return (6);
	return (0);
}

/**
 * @brief Initialize the forks
 *
 * @param shared structure of shared variables
 * @param philo philosopher structure
 * @param count number of element
 * @return int
 */
int	init_forks(t_shared *shared, t_philo *philo, int count)
{
	int	index;

	index = 0;
	while (index < count)
	{
		if (pthread_mutex_init(&shared->forks[index], NULL) != 0)
		{
			free_shared(shared, count, 0);
			free_philos(philo);
			return (4);
		}
		shared->is_fork_taken[index] = 0;
		index++;
	}
	return (0);
}

/**
 * @brief Initialize the mutex
 *
 * @param shared structure of shared variables
 * @param philo philosopher structure
 * @param count number of element
 * @return int
 */
int	init_mutex(t_shared *shared, t_philo *philo, int count)
{
	int	index;

	index = init_forks_mutex(shared, count);
	if (index != 0)
	{
		free_shared(shared, 0, index);
		free_philos(philo);
		return (3);
	}
	index = 0;
	pthread_mutex_init(&shared->mutex_nb_eat, NULL);
	return (0);
}

/* int	init_mutex_each_nb_eat(t_shared *shared, t_philo *philo, int count,
	int index)
{
	while (index < count)
	{
		if (pthread_mutex_init(&philo[index].mutex_nb_eat, NULL) != 0)
		{
			free_shared(shared, count, 0);
			free_philos(philo);
			return (4);
		}
		shared->is_fork_taken[index] = 0;
		index++;
	}
}
 */
