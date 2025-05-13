/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:56:48 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/13 13:17:40 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <time.h>

void	ft_usleep(size_t wait_time)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < wait_time)
		usleep(500);
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

int	does_have_time(t_philo *philo, enum e_philo_state p_state)
{
	int		time;
	size_t	time2;

	if (philo == NULL)
		return (-1);
	if (p_state == TOOK_FORK || p_state == EATING)
		time = philo->rules->time_to_eat;
	if (p_state == SLEEPING)
		time = philo->rules->time_to_die;
	else
		time = -1;
	pthread_mutex_lock(&philo->shared->meal_access);
	time2 = get_time();
	printf("p %d, last %zu, time %zu, calc %zu, now %zu : result %d\n",
		philo->id, philo->time.last_meal, (size_t)time, philo->time.last_meal
		+ time, time2, philo->time.last_meal + time > time2);
	if ((size_t)(philo->time.last_meal + time) > time2)
	{
		pthread_mutex_lock(&philo->shared->read_shared);
		philo->shared->is_running = FALSE;
		pthread_mutex_unlock(&philo->shared->read_shared);
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
		usleep(10);
	}
}
