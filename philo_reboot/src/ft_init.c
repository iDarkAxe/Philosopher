/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:03:57 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/13 14:05:34 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_const_rules rules, t_shared *shared, t_philo **philo)
{
	int	count;

	*philo = ft_calloc(sizeof(t_philo), rules.nb_philo);
	if (*philo == NULL)
		return (1);
	count = 0;
	while (count < rules.nb_philo)
	{
		(*philo)[count].id = count;
		(*philo)[count].shared = shared;
		(*philo)[count].const_rules = ft_calloc(sizeof(t_const_rules), 1);
		if ((*philo)[count].const_rules == NULL)
		{
			free_philos(*philo, count);
			return (2);
		}
		ft_memcpy((void *)(*philo)[count].const_rules, (void *)&rules,
			sizeof(t_const_rules));
		count++;
	}
	return (0);
}

int	init_forks_mutex(t_shared *shared, int count)
{
	if (pthread_mutex_init(&shared->print, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&shared->read_shared, NULL) != 0)
		return (2);
	shared->forks_nbr = NULL;
	shared->forks = ft_calloc(sizeof(pthread_mutex_t), count);
	if (shared->forks == NULL)
		return (3);
	shared->forks_nbr = ft_calloc(sizeof(enum e_bool), count);
	if (shared->forks_nbr == NULL)
		return (4);
	return (0);
}

int	init_mutex(t_shared *shared, t_philo *philo, int count)
{
	int	index;

	index = init_forks_mutex(shared, count);
	if (index != 0)
	{
		free_shared(shared, 0, 0);
		free_philos(philo, count);
		return (3);
	}
	index = 0;
	while (index < count)
	{
		if (pthread_mutex_init(&shared->forks[index], NULL) != 0)
		{
			free_shared(shared, count, 0);
			free_philos(philo, count);
			return (4);
		}
		shared->forks_nbr[index] = TRUE;
		index++;
	}
	return (0);
}
