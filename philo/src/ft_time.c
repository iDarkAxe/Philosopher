/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:56:48 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/16 12:36:16 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "routine.h"
#include "ft_time.h"
#include <stdio.h>
#include <time.h>

/**
 * @brief Special usleep function that checks if the simulation is running
 * during it's sleep time
 * 
 * @param wait_time time to wait in ms
 * @param philo philosopher structure
 */
void	ft_usleep(size_t wait_time, t_philo *philo)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < wait_time)
	{
		if (is_running(philo) != 0)
			return ;
		usleep(DELAY);
	}
}

/**
 * @brief Return the current time in ms
 * 
 * @return size_t time in ms
 */
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

/**
 * @brief Get the delta time since the start of the simulation
 * 
 * @param philo philosopher structure
 * @return size_t time in ms
 */
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

/**
 * @brief Check if the philosopher has time to do something
 * 
 * @param philo philosopher structure
 * @param p_state state of the philosopher
 * @return int 1 if the philosopher has time, 0 otherwise
 */
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
	pthread_mutex_lock(&philo->shared->read_shared);
	philo->shared->ready++;
	pthread_mutex_unlock(&philo->shared->read_shared);
	while (1)
	{
		pthread_mutex_lock(&philo->shared->read_shared);
		if (*value1 == *value2)
		{
			pthread_mutex_unlock(&philo->shared->read_shared);
			return ;
		}
		pthread_mutex_unlock(&philo->shared->read_shared);
		usleep(DELAY);
	}
}
