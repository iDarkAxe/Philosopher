/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:56:48 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/11 16:36:56 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <time.h>

static struct timeval	getdeltatime(struct timeval start_time);

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

/**
 * @brief Function that returns the delta time
 * between the start_time and the current time
 * @deprecated not used anywhere now
 *
 * @param start_time (struct timeval)
 * @return struct timeval
 */
__attribute__ ((__deprecated__))
__attribute__ ((__unused__))
static struct timeval	getdeltatime(struct timeval start_time)
{
	struct timeval	timer;

	if (gettimeofday(&timer, NULL) != 0)
	{
		timer.tv_sec = 0;
		timer.tv_usec = 0;
	}
	timer.tv_sec = timer.tv_sec - start_time.tv_sec;
	timer.tv_usec = timer.tv_usec - start_time.tv_usec;
	if (timer.tv_usec < 0)
	{
		timer.tv_sec -= 1;
		timer.tv_usec += 1000000;
	}
	return (timer);
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
