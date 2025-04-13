/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:02:20 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/13 17:25:28 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

// TODO supprimer le count et l'index

/**
 * @brief Free the philo structure
 *
 * @param philo philosopher structure
 * @param count number of element
 */
void	free_philos(t_philo *philo, int count)
{
	int	index;

	index = 0;
	(void)count;
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
	while (shared->forks != NULL && count > 0)
		pthread_mutex_destroy(&shared->forks[--count]);
	if (flag == 2 || flag == 0)
		pthread_mutex_destroy(&shared->print);
	pthread_mutex_destroy(&shared->read_shared);
	if (shared->forks != NULL)
	{
		free(shared->forks);
		shared->forks = NULL;
	}
	if (shared->forks_nbr != NULL)
	{
		free(shared->forks_nbr);
		shared->forks_nbr = NULL;
	}
}
