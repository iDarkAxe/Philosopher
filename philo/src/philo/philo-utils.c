/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo-utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:23:43 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/13 13:15:53 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	is_running(t_philo *philo);
int	has_everyone_ate(t_philo *philo);

int	is_running(t_philo *philo)
{
	if (philo == NULL)
		return (0);
	pthread_mutex_lock(&philo->shared->read_shared);
	if (philo->shared->is_running == TRUE)
	{
		pthread_mutex_unlock(&philo->shared->read_shared);
		return (1);
	}
	pthread_mutex_unlock(&philo->shared->read_shared);
	return (0);
}

int	has_everyone_ate(t_philo *philo)
{
	int	index;

	if (philo == NULL)
		return (0);
	pthread_mutex_lock(&philo->shared->read_shared);
	if (philo->rules->nb_eat_target < 0 || (WAIT_EVERYONE == 1
			&& philo->rules->nb_philo != philo->shared->ready))
	{
		pthread_mutex_unlock(&philo->shared->read_shared);
		return (0);
	}
	pthread_mutex_unlock(&philo->shared->read_shared);
	index = 0;
	pthread_mutex_lock(&philo->shared->meal_access);
	while (index < philo->rules->nb_philo)
	{
		if (philo[index].nb_eat < philo->rules->nb_eat_target)
		{
			pthread_mutex_unlock(&philo->shared->meal_access);
			return (0);
		}
		index++;
	}
	pthread_mutex_unlock(&philo->shared->meal_access);
	return (1);
}

/**
 * @brief Print message for the state of the philosopher
 *
 * @param philo philosopher
 * @param p_state philosopher state to print
 */
void	print_message(t_philo *philo, enum e_philo_state p_state)
{
	static const char	*state[] = {"has taken a fork", "is eating",
		"is sleeping", "is thinking", "died"};

	(void)state;
	(void)p_state;
	pthread_mutex_lock(&philo->shared->print);
	if (is_running(philo) != 0)
		printf("%ld\t%d\t%s\n", get_time() - philo->time.born_time, philo->id,
			state[(int)p_state]);
	pthread_mutex_unlock(&philo->shared->print);
}
// printf("%ld\t%d\t%s\n", get_time() - philo->time.born_time, philo->id,
// 			state[(int)DIED]);
