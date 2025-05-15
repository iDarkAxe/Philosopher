/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:56:48 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/15 18:01:28 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <time.h>

void	ft_usleep(size_t wait_time, t_philo *philo)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < wait_time)
	{
		if (is_running(philo) != 0)
			return ;
		usleep(500);
	}
}

size_t	get_time(void)
{
	struct timeval	timer;

	if (gettimeofday(&timer, NULL) != 0)
	{
		timer.tv_sec = 0;
		timer.tv_usec = 0;
		write(2, "gettimeofday : error\n", 22);
	}
	return ((size_t)(timer.tv_sec * 1000 + timer.tv_usec / 1000));
}

size_t	get_dtime(t_philo *philo)
{
	struct timeval	timer;

	if (philo == NULL)
		return (0);
	if (gettimeofday(&timer, NULL) != 0)
	{
		timer.tv_sec = 0;
		timer.tv_usec = 0;
		write(2, "gettimeofday : error\n", 22);
	}
	timer.tv_sec -= philo->rules->start.tv_sec;
	timer.tv_usec -= philo->rules->start.tv_usec;
	if (timer.tv_usec < 0)
	{
		timer.tv_sec -= 1;
		timer.tv_usec += 1000000;
	}
	return ((size_t)(timer.tv_sec * 1000 + timer.tv_usec / 1000));
}

int	does_have_time(t_philo *philo, enum e_philo_state p_state)
{
	int	timer;

	if (philo == NULL)
		return (-1);
	if (p_state == TOOK_FORK || p_state == EATING)
		timer = philo->rules->time_to_eat;
	else if (p_state == SLEEPING)
		timer = philo->rules->time_to_sleep;
	else
		timer = 1;
	pthread_mutex_lock(&philo->shared->meal_access);
	if ((get_dtime(philo) + (size_t)timer) > philo->time.last_meal
		+ (size_t)philo->rules->time_to_die)
	{
		ft_usleep((size_t)timer, philo);
		philo_died(philo);
		pthread_mutex_unlock(&philo->shared->meal_access);
		return (1);
	}
	pthread_mutex_unlock(&philo->shared->meal_access);
	return (0);
}

void	waits_for_equals(pthread_mutex_t *mutex, const int *const value1,
		const int *const value2)
{
	while (1)
	{
		pthread_mutex_lock(mutex);
		if (*value1 == *value2)
		{
			pthread_mutex_unlock(mutex);
			return ;
		}
		pthread_mutex_unlock(mutex);
		usleep(500);
	}
}
