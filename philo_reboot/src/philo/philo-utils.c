/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo-utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:23:43 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/11 16:41:05 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

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

	pthread_mutex_lock(&philo->shared->print);
	if (is_running(philo) == 0)
		printf("%ld\t%d\t%s\n", get_time() - philo->time.born_time, philo->id,
			state[(int)DIED]);
	else
		printf("%ld\t%d\t%s\n", get_time() - philo->time.born_time, philo->id,
			state[(int)p_state]);
	pthread_mutex_unlock(&philo->shared->print);
}
