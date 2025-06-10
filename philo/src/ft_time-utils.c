/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time-utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:56:48 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/10 13:24:34 by ppontet          ###   ########lyon.fr   */
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
	if (philo == NULL || value1 == NULL || value2 == NULL)
	{
		write(2, "wait_everyone : NULL pointer\n", 30);
		return ;
	}
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

// FIXME needs to wait for resting time
// Attendre le temps restant
	// ft_usleep()
/**
 * @brief Check if the philosopher has time to do something
 *
 * @param philo philosopher structure
 * @param p_state state of the philosopher
 * @return int 0 if the philosopher has time, 1 otherwise
 */
/* int	does_not_have_time(t_philo *philo, enum e_philo_state p_state)
{
	int				timer;
	struct timeval	tv;

	if (philo == NULL)
		return (-1);
	if (p_state == TOOK_FORK || p_state == EATING)
		timer = philo->rules->time_to_eat;
	else if (p_state == SLEEPING)
		timer = philo->rules->time_to_sleep;
	else
		timer = 1;
	pthread_mutex_lock(&philo->shared->mutex_nb_eat);
	tv = get_time();
	if (compare_time(&philo->time.last_meal, &tv) == 1)
	{
		philo_died(philo);
		pthread_mutex_unlock(&philo->shared->mutex_nb_eat);
		return (1);
	}
	pthread_mutex_unlock(&philo->shared->mutex_nb_eat);
	return (0);
} */
