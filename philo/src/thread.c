/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:19:50 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/16 16:55:12 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "routine.h"

/**
 * @brief Function to create only one thread and uses a special routine
 * 
 * @param rules structure of const rules
 * @param shared structure of shared variables
 * @param philo head of philosopher structure
 * @return int 0 OK, error otherwise
 */
int	thread_createone(t_rules *rules, t_shared *shared, t_philo *philo)
{
	if (!rules || !shared || !philo)
		return (1);
	if (gettimeofday(&rules->start, NULL) != 0)
		return (1);
	if (pthread_create(&philo[0].philosopher, NULL,
			(void *(*)(void *))one_philo_routine, (void *)&philo[0]) != 0)
	{
		free_philos(philo);
		free_shared(shared, rules->nb_philo, 0);
		return (1);
	}
	return (0);
}

/**
 * @brief Function to create the threads
 *
 * @param rules structure of const rules
 * @param shared structure of shared variables
 * @param philo head of philosopher structure
 * @return int 0 if successful, 1 otherwise
 */
int	thread_create(t_rules *rules, t_shared *shared, t_philo *philo)
{
	int	count;

	if (!rules || !shared || !philo)
		return (1);
	count = 0;
	if (gettimeofday(&rules->start, NULL) != 0)
		return (1);
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
	return (0);
}

/**
 * @brief Function to join all the threads
 * 
 * @param rules structure of const rules
 * @param philo head of philosopher structure
 * @return int 0 OK, error otherwise
 */
int	thread_join(t_rules *rules, t_philo *philo)
{
	int	count;

	if (!rules || !philo)
		return (1);
	count = 0;
	while (count < rules->nb_philo)
	{
		pthread_join(philo[count].philosopher, NULL);
		count++;
	}
	return (0);
}
