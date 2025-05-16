/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time_old.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:56:48 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/16 17:26:09 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <time.h>

static struct timeval	getdeltatime(struct timeval start_time);
static void				ft_usleep(size_t wait_time, t_philo *philo);

/**
 * @brief Special usleep function that checks if the simulation is running
 * during it's sleep time
 * 
 * @param wait_time time to wait in ms
 * @param philo philosopher structure
 */
__attribute__ ((__deprecated__))
__attribute__ ((__unused__))
static void	ft_usleep(size_t wait_time, t_philo *philo)
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
