/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:02:20 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/18 16:02:26 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

/**
 * @brief Free the philo structure
 *
 * @param philo philosopher structure
 */
void	free_philos(t_philo *philo)
{
	if (philo != NULL)
		free(philo);
}

/**
 * @brief Free all the data in s_shared structure
 *
 * @param shared structure of shared variables
 * @param count number of element
 * @param flag specific for print mutex
 */
void	free_shared(t_shared *shared, int count, int flag)
{
	int	temp;

	temp = count;
	while (shared->forks != NULL && temp > 0)
		pthread_mutex_destroy(&shared->forks[--temp]);
	if (flag == 2 || flag == 0)
		pthread_mutex_destroy(&shared->mutex_printing);
	pthread_mutex_destroy(&shared->mutex_is_running);
	temp = count;
	while (shared->forks != NULL && temp > 0)
		pthread_mutex_destroy(&shared->forks[--temp]);
	if (shared->forks != NULL)
	{
		free(shared->forks);
		shared->forks = NULL;
	}
	if (shared->is_fork_taken != NULL)
	{
		free(shared->is_fork_taken);
		shared->is_fork_taken = NULL;
	}
}
