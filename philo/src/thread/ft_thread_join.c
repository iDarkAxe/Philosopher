/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread_join.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 17:53:27 by ppontet           #+#    #+#             */
/*   Updated: 2025/03/18 14:24:36 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

/**
 * @brief Check if all threads dead or not
 * Each thread update it's state itself
 * If a thread get killed by something, there's no way to end the function
 * 
 * @param rules rules of the program
 * @return int 1 is all threads are dead, 
 * otherwise 0 is at least one thread is not dead (LIVING or NOT_STARTED)
 */
int	are_all_threads_dead(const t_const_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		if (rules->philo[i].living_state != DIED)
			return (0);
		i++;
	}
	if (DEBUG == 1)
		printf("All philos are dead\n");
	i = 0;
	while (i < rules->nb_philo)
	{
		if (pthread_join(rules->philo[i].philosopher, NULL) != 0)
			return (2);
		i++;
	}
	if (DEBUG == 1)
		printf("And all threads joined\n");
	return (1);
}

/**
 * @brief Check if all threads dead or not
 * Each thread update it's state itself
 * If a thread get killed by something, there's no way to end the function
 * 
 * @param rules rules of the program
 * @return int 1 is all threads are dead, 
 * otherwise 0 is at least one thread is not dead (LIVING or NOT_STARTED)
 */
int	are_all_threads_state(const t_const_rules *rules, enum e_living_state state)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		if (rules->philo[i].living_state != state)
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Create all threads and detach them immediately
 * 
 * @param rules rules of the program
 * @return int 0 OK, otherwise error (1)
 */
int	thread_creation(t_const_rules *rules, t_shared_ressources *shared)
{
	int		i;

	i = 0;
	while (i < rules->nb_philo)
	{
		if (pthread_create(&rules->philo[i].philosopher, NULL, &philo_routine,
				&rules->philo[i]) != 0)
		{
			free_philo(rules, shared, i);
			write(2, "Error pthread_create\n", 22);
			return (1);
		}
		i++;
		rules->is_everyone_ready++;
	}
	return (0);
}
