/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo-utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:23:43 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/22 09:54:30 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_time.h"
#include "philo.h"
#include "routine.h"
#include <stdio.h>

int		is_sim_running(t_philo *philo);
int		has_everyone_ate(t_philo *philo);

/**
 * @brief Check if it's running
 *
 * @param philo philo structure
 * @return int 1 is running, 0 otherwise
 */
int	is_sim_running(t_philo *philo)
{
	if (philo == NULL)
		return (0);
	pthread_mutex_lock(&philo->shared->mutex_is_running);
	if (philo->shared->is_running == 1)
	{
		pthread_mutex_unlock(&philo->shared->mutex_is_running);
		return (1);
	}
	pthread_mutex_unlock(&philo->shared->mutex_is_running);
	return (0);
}

/**
 * @brief Function to check if all philosophers have eaten enough
 *
 * @param philo philosopher structure
 * @return int 1 if all philosophers have eaten enough, 0 otherwise
 */
int	has_everyone_ate(t_philo *philo)
{
	int	index;

	if (philo == NULL)
		return (0);
	if (philo->rules->nb_eat_target < 0)
		return (0);
	index = 0;
	while (index < philo->rules->nb_philo)
	{
		pthread_mutex_lock(&philo->shared->mutex_nb_eat);
		if (philo[index].nb_eat < philo->rules->nb_eat_target)
		{
			pthread_mutex_unlock(&philo->shared->mutex_nb_eat);
			return (0);
		}
		index++;
		pthread_mutex_unlock(&philo->shared->mutex_nb_eat);
	}
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
	struct timeval		timer;
	static const char	*state[] = {"has taken a fork", "is eating",
		"is sleeping", "is thinking", "died"};

	if (is_sim_running(philo) == 0)
		return ;
	pthread_mutex_lock(&philo->shared->mutex_printing);
	timer = get_time();
	timer.tv_sec -= philo->rules->start.tv_sec;
	timer.tv_usec -= philo->rules->start.tv_usec;
	printf("%ld\t%d\t%s\n", (size_t)(timer.tv_sec * 1000 + timer.tv_usec
			/ 1000), philo->id, state[(int)p_state]);
	pthread_mutex_unlock(&philo->shared->mutex_printing);
}
