/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 12:12:39 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/10 13:24:14 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_time.h"
#include "philo.h"
#include "routine.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

static void	observer_check_timings(const t_rules *rules, t_philo *philo,
				int *count);

/**
 * @brief Simple task for observer to verify the timings of each philo
 * 
 * @param rules rules structure
 * @param philo philo structure
 * @param count actual philo checked
 */
void	observer_check_timings(const t_rules *rules, t_philo *philo, int *count)
{
	struct timeval	timer;
	struct timeval	limit;

	if (rules == NULL || philo == NULL || count == NULL)
	{
		write(2, "observer_check_timings : NULL pointer\n", 38);
		return ;
	}
	if (*count >= rules->nb_philo)
		*count = 0;
	timer = get_time();
	pthread_mutex_lock(&philo->shared->mutex_nb_eat);
	limit = philo[*count].time.last_meal;
	add_ms_timeval(&limit, rules->time_to_die);
	if (compare_time(&timer, &limit) == 1)
		philo_died(&philo[*count]);
	pthread_mutex_unlock(&philo->shared->mutex_nb_eat);
	(*count)++;
}

/**
 * @brief Function to observe the philos
 *
 * @param philo head of philosopher structure
 */
void	observer_task(const t_rules *rules, t_philo *philo)
{
	int				count;
	
	if (rules == NULL || philo == NULL)
	{
		write(2, "observer_task : NULL pointer\n", 30);
		return ;
	}
	count = 0;
	while (is_sim_running(philo) == 1)
	{
		observer_check_timings(rules, philo, &count);
	}
}

/**
 * @brief Function to observe the philos
 *
 * @param philo head of philosopher structure
 */
void	observer_task_eat(const t_rules *rules, t_philo *philo)
{
	int				count;

	if (rules == NULL || philo == NULL)
	{
		write(2, "observer_task_eat : NULL pointer\n", 30);
		return ;
	}
	count = 0;
	while (is_sim_running(philo) == 1)
	{
		observer_check_timings(rules, philo, &count);
		if (has_everyone_ate(philo) == 1)
		{
			pthread_mutex_lock(&philo->shared->mutex_is_running);
			philo->shared->is_running = 0;
			pthread_mutex_unlock(&philo->shared->mutex_is_running);
			break ;
		}
	}
}
