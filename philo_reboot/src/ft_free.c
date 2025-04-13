/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:02:20 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/13 14:06:25 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

void free_philos(t_philo *philo, int count)
{
	int index;

	index = 0;
	while (philo != NULL && index < count)
	{
		free(philo[index].const_rules);
		index++;
	}
	if (philo != NULL)
		free(philo);
}

void free_shared(t_shared *shared, int count, int flag)
{
	while (shared->forks != NULL && count >= 0)
		pthread_mutex_destroy(&shared->forks[count--]);
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
