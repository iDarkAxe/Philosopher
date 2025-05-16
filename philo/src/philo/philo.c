/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 17:56:02 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/16 15:28:20 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_time.h"
#include "philo.h"
#include "routine.h"
#include <stdio.h>

/**
 * @brief Philosopher's death detected by the observer
 *
 * @param philo philosopher structure
 */
void	philo_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->is_running_access);
	if (philo->shared->is_running == 1)
	{
		pthread_mutex_lock(&philo->shared->print);
		printf("%ld\t%d\tdied\n", get_dtime(philo), philo->id);
		pthread_mutex_unlock(&philo->shared->print);
		philo->shared->is_running = 0;
	}
	pthread_mutex_unlock(&philo->shared->is_running_access);
}

/**
 * @brief Philosopher's routine when he is alone
 *
 * @param ptr pointer to the first philosopher structure
 * @return int 1 if the routine is successful, 0 otherwise
 */
void	*one_philo_routine(void *ptr)
{
	t_philo	*philo;
	size_t	timer;

	if (ptr == NULL)
		return (NULL);
	philo = (t_philo *)ptr;
	philo->time.born_time = get_time();
	philo->time.last_meal = philo->time.born_time;
	print_message(philo, THINKING);
	print_message(philo, TOOK_FORK);
	timer = get_time();
	if (timer < philo->time.born_time + (size_t)philo->rules->time_to_die)
		usleep((__useconds_t)(philo->time.born_time
				+ (size_t)philo->rules->time_to_die - timer) * 1000);
	philo_died(philo);
	return (NULL);
}

/**
 * @brief Philosopher's routine
 *
 * @param philo pointer to the philosopher structure
 * @return int 1 if the routine is successful, 0 otherwise
 */
int	philo_routine(t_philo *philo)
{
	if (philo == NULL)
		return (0);
	print_message(philo, THINKING);
	if (try_eating(philo) == 0)
		return (0);
	if (does_have_time(philo, SLEEPING) == 1)
		return (0);
	print_message(philo, SLEEPING);
	usleep((__useconds_t)philo->rules->time_to_sleep * 1000);
	return (1);
}

// TO desynchronise even philos
// if (philo->id % 2 == 0)
// 	ft_usleep(1);

/**
 * @brief Starting point of the philosopher's thread
 *
 * @param ptr pointer to the philosopher structure
 * @return void* NULL
 */
void	*start_routine(void *ptr)
{
	t_philo	*philo;

	if (ptr == NULL)
		return (NULL);
	philo = (t_philo *)ptr;
	philo->time.born_time = get_time();
	philo->time.last_meal = philo->time.born_time;
	if (WAIT_EVERYONE == 1)
		wait_everyone(philo, &philo->shared->ready, &philo->rules->nb_philo);
	while (is_running(philo))
	{
		if (philo_routine(philo) == 0)
			return (NULL);
	}
	philo_died(philo);
	return (NULL);
}
