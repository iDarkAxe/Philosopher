/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:56:48 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/31 12:17:51 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_time.h"
#include "philo.h"
#include "routine.h"
#include <stdio.h>
#include <time.h>

/**
 * @brief Return the current time in ms
 *
 * @return size_t time in ms
 */
struct timeval	get_time(void)
{
	struct timeval	timer;

	if (gettimeofday(&timer, NULL) != 0)
	{
		timer.tv_sec = 0;
		timer.tv_usec = 0;
		write(2, "gettimeofday : error\n", 22);
	}
	return (timer);
}

/**
 * @brief Get the delta time since the born time of the philo
 *
 * @param philo philosopher structure
 * @return size_t time in ms
 */
struct timeval	get_dtime(t_philo *philo)
{
	struct timeval	timer;

	if (philo == NULL)
		return ((struct timeval){.tv_sec = 0, .tv_usec = 0});
	timer = get_time();
	timer.tv_sec -= philo->time.born_time.tv_sec;
	timer.tv_usec -= philo->time.born_time.tv_usec;
	if (timer.tv_usec < 0)
	{
		timer.tv_sec -= 1;
		timer.tv_usec += 1000000;
	}
	return (timer);
}

/**
 * @brief Compare two struct timeval simply
 * if t1 is more old than t2, it will return -1
 * if t1 is more recent than t2, it will return 1
 * it returns 0 if they are equals
 *
 * @param t1 first timeval
 * @param t2 second timeval
 * @return int -1 is t1 older, 1 is t2 older, 0 equals
 */
int	compare_time(struct timeval *t1, struct timeval *t2)
{
	if (t1->tv_sec < t2->tv_sec)
		return (-1);
	if (t1->tv_sec > t2->tv_sec)
		return (1);
	if (t1->tv_usec < t2->tv_usec)
		return (-1);
	if (t1->tv_usec > t2->tv_usec)
		return (1);
	return (0);
}

/**
 * @brief Add milliseconds to a timeval and returns it value
 *
 * @param tv timeval to modify
 * @param milliseconds value to add
 * @return struct timeval* tv modified (same)
 */
struct timeval	*add_ms_timeval(struct timeval *tv, long milliseconds)
{
	tv->tv_sec += milliseconds / 1000;
	milliseconds %= 1000;
	tv->tv_usec += milliseconds * 1000;
	if (tv->tv_usec >= 1000000)
	{
		tv->tv_sec += tv->tv_usec / 1000000;
		tv->tv_usec %= 1000000;
	}
	return (tv);
}

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
	add_ms_timeval(&goal_time, wait_time);
	current_time = get_time();
	while (compare_time(&current_time, &goal_time) < 0)
	{
		if (is_sim_running(philo) != 0)
			return ;
		usleep(DELAY);
		current_time = get_time();
	}
}
