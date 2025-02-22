/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 17:56:02 by ppontet           #+#    #+#             */
/*   Updated: 2025/02/22 17:59:36 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int	free_philo(t_rules *rules, int count)
{
	int	i;

	if (rules->philo != NULL)
	{
		free((void *)rules->philo);
		rules->philo = NULL;
	}
	i = 0;
	while (rules->forks != NULL && i < count)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		i++;
	}
	if (rules->forks != NULL)
	{
		free((void *)rules->forks);
		rules->forks = NULL;
	}
	(void)count;
	return (0);
}

int	init_philo(t_rules *rules)
{
	int	i;

	rules->forks = NULL;
	rules->philo = ft_calloc(sizeof(t_philo), rules->nb_philo);
	if (rules->philo == NULL)
		return (1);
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->nb_philo);
	if (rules->forks == NULL)
		return (1);
	i = 0;
	rules->is_everyone_ready = 0;
	while (i < rules->nb_philo)
	{
		rules->philo[i].id = i;
		rules->philo[i].nb_eat = rules->nb_eat;
		rules->philo[i].rules = rules;
		rules->philo[i].living_state = NOT_STARTED;
		if (pthread_mutex_init(&rules->forks[i], NULL) != 0)
		{
			free_philo(rules, i);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo			*philo;
	struct timeval	time_at_death;

	philo = (t_philo *)arg;
	if (philo == NULL)
		return (NULL);
	while (philo->rules->is_everyone_ready != philo->rules->nb_philo)
		usleep(10);
	philo->living_state = LIVING;
	pthread_mutex_lock(&philo->rules->is_printing);
	printf("philo %d is alive\n", philo->id);
	pthread_mutex_unlock(&philo->rules->is_printing);
	usleep(100000);
	pthread_mutex_lock(&philo->rules->is_printing);
	gettimeofday(&time_at_death, NULL);
	printf("philo %d is dying at %ld:%ld\n", philo->id, time_at_death.tv_sec
		- philo->rules->time_at_start.tv_sec, time_at_death.tv_usec);
	pthread_mutex_unlock(&philo->rules->is_printing);
	philo->living_state = DEAD;
	return (NULL);
}
