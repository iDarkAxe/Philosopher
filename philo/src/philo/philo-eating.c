/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo-eating.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:09:59 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/15 14:10:48 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		if (is_running(philo) == 0)
			break ;
		if (philo->shared->forks_nbr[assign_fork] == FALSE)
		{
			philo->shared->forks_nbr[assign_fork] = TRUE;
			break ;
		}
		pthread_mutex_unlock(&philo->shared->forks[assign_fork]);
		usleep(DELAY);
	}
	pthread_mutex_unlock(&philo->shared->forks[assign_fork]);
	if (is_running(philo) == 0)
		return (0);
	return (1);
}

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
	philo->shared->forks_nbr[assign_fork] = FALSE;
	pthread_mutex_unlock(&philo->shared->forks[assign_fork]);
	return (1);
}

int	try_eating(t_philo *philo)
{
	if (philo == NULL)
		return (0);
	if (try_taking_fork(philo, 1) == 0)
		return (0);
	print_message(philo, TOOK_FORK);
	if (try_taking_fork(philo, 0) == 0)
		return (0);
	print_message(philo, TOOK_FORK);
	if (does_have_time(philo, EATING) == 1)
		return (0);
	pthread_mutex_lock(&philo->shared->meal_access);
	print_message(philo, EATING);
	philo->time.last_meal = get_dtime(philo);
	philo->nb_eat += 1;
	pthread_mutex_unlock(&philo->shared->meal_access);
	usleep((__useconds_t)philo->rules->time_to_eat * 1000);
	set_back_fork(philo, 1);
	set_back_fork(philo, 0);
	return (1);
}
