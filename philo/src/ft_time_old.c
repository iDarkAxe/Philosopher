/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time_old.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:56:48 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/18 12:38:11 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "ft_time.h"
#include <time.h>

static struct timeval	getdeltatime(struct timeval start_time);

/**
 * @brief Special usleep function that checks if the simulation is running
 * during it's sleep time
 * 
 * @param wait_time time to wait in ms
 * @param philo philosopher structure
 */
void	ft_usleep(__useconds_t wait_time, t_philo *philo)
{
	struct timeval	goal_time;
	struct timeval	current_time;

	goal_time = get_time();
	add_ms_tv(&goal_time, wait_time);
	current_time = get_time();
	while (compare_timeval(&current_time, &goal_time) < 0)
	{
		if (is_sim_running(philo) != 0)
			return ;
		usleep(DELAY);
		current_time = get_time();
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
