/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time-utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:56:48 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/11 10:10:27 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "ft_time.h"
#include "routine.h"
#include <time.h>

/**
 * @brief Wait for everyone to be ready before starting the simulation
 *
 * @param philo philosopher structure
 * @param value1 pointer to the value to check
 * @param value2 pointer to the value to compare with
 */
void	wait_everyone(t_philo *philo, const int *const value1,
		const int *const value2)
{
	if (!philo || !value1 || !value2)
		return ;
	pthread_mutex_lock(&philo->shared->mutex_ready);
	philo->shared->ready++;
	pthread_mutex_unlock(&philo->shared->mutex_ready);
	while (1)
	{
		pthread_mutex_lock(&philo->shared->mutex_ready);
		if (*value1 == *value2)
		{
			pthread_mutex_unlock(&philo->shared->mutex_ready);
			return ;
		}
		pthread_mutex_unlock(&philo->shared->mutex_ready);
		usleep(DELAY);
	}
}
