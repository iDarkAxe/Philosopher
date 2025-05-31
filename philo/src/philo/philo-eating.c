/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo-eating.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:09:59 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/31 13:23:13 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "routine.h"
#include "ft_time.h"
#include <stdio.h>

static int	is_philo_even_take_fork(t_philo *philo);
static int	is_philo_even_setback_fork(t_philo *philo);

/**
 * @brief Try taking a fork
 * 
 * @param philo philo structure
 * @param is_left 1 for left fork, 0 for right fork
 * @return int 
 */
int	try_taking_fork(t_philo *philo, char is_left)
{
	int	assign_fork;

	if (philo == NULL)
		return (0);
	if (is_left == 1)
		assign_fork = philo->id;
	else
		assign_fork = (philo->id + 1) % philo->rules->nb_philo;
	while (1)
	{
		pthread_mutex_lock(&philo->shared->forks[assign_fork]);
		if (is_sim_running(philo) == 0)
			break ;
		if (philo->shared->is_fork_taken[assign_fork] == 0)
		{
			philo->shared->is_fork_taken[assign_fork] = 1;
			break ;
		}
		pthread_mutex_unlock(&philo->shared->forks[assign_fork]);
		usleep(DELAY);
	}
	pthread_mutex_unlock(&philo->shared->forks[assign_fork]);
	if (is_sim_running(philo) == 0)
		return (0);
	return (1);
}

/**
 * @brief Set back the fork object to not taken
 * 
 * @param philo philo structure
 * @param is_left 1 for left fork, 0 for right fork
 * @return int 1 if successful, 0 otherwise
 */
int	set_back_fork(t_philo *philo, char is_left)
{
	int	assign_fork;

	if (philo == NULL)
		return (0);
	if (is_left == 1)
		assign_fork = philo->id;
	else
		assign_fork = (philo->id + 1) % philo->rules->nb_philo;
	pthread_mutex_lock(&philo->shared->forks[assign_fork]);
	philo->shared->is_fork_taken[assign_fork] = 0;
	pthread_mutex_unlock(&philo->shared->forks[assign_fork]);
	return (1);
}

static int	is_philo_even_take_fork(t_philo *philo)
{
	char	first_fork;
	char	second_fork;

	if (philo->id % 2 == 0)
	{
		first_fork = 0;
		second_fork = 1;
	}
	else
	{
		first_fork = 1;
		second_fork = 0;
	}
	if (!try_taking_fork(philo, first_fork))
		return (0);
	print_message(philo, TOOK_FORK);
	if (!try_taking_fork(philo, second_fork))
	{
		set_back_fork(philo, first_fork);
		return (0);
	}
	print_message(philo, TOOK_FORK);
	return (1);
}

static int	is_philo_even_setback_fork(t_philo *philo)
{
	char	first_fork;
	char	second_fork;

	if (philo->id % 2 == 0)
	{
		first_fork = 1;
		second_fork = 0;
	}
	else
	{
		first_fork = 0;
		second_fork = 1;
	}
	set_back_fork(philo, first_fork);
	set_back_fork(philo, second_fork);
	return (1);
}

/**
 * @brief Try eating, if there is no time remaining, 
 * Stops it's execution and return 0
 * 
 * @param philo philo structure
 * @return int 1 if successful, 0 otherwise
 */
int	try_eating(t_philo *philo)
{
	if (philo == NULL)
		return (0);
	if (philo->id % 2 == 0)
		usleep(2000);
	if (is_philo_even_take_fork(philo) != 1)
		return (0);
	pthread_mutex_lock(&philo->shared->mutex_nb_eat);
	print_message(philo, EATING);
	philo->time.last_meal = get_time();
	philo->nb_eat += 1;
	pthread_mutex_unlock(&philo->shared->mutex_nb_eat);
	usleep((__useconds_t)philo->rules->time_to_eat * 1000);
	if (is_philo_even_setback_fork(philo) == 0)
		return (0);
	return (1);
}
