/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 17:56:02 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/11 16:40:48 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_routine(t_philo *philo)
{
	if (philo == NULL)
		return ;
	print_message(philo, TOOK_FORK);
}

// TO desynchronise even philos
// if (philo->id % 2 == 0)
// 	ft_usleep(1);
void	*start_routine(void *ptr)
{
	t_philo	*philo;
	size_t	index;

	if (ptr == NULL)
		return (NULL);
	philo = (t_philo *)ptr;
	philo->time.born_time = get_time();
	philo->time.last_meal = get_time();
	print_message(philo, THINKING);
	pthread_mutex_lock(&philo->shared->read_shared);
	philo->shared->ready++;
	pthread_mutex_unlock(&philo->shared->read_shared);
	waits_for_equals(&philo->shared->read_shared, &philo->shared->ready,
		&philo->const_rules->nb_philo);
	index = 0;
	while (index < 3 && is_running(philo) == 0)
	{
		philo_routine(philo);
		index++;
	}
	return (NULL);
}
