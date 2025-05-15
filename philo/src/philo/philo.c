/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 17:56:02 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/15 17:59:29 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	philo_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->is_running_access);
	if (philo->shared->is_running == TRUE)
	{
		printf("%ld\t%d\tdied\n", get_dtime(philo), philo->id);
		philo->shared->is_running = FALSE;
	}
	pthread_mutex_unlock(&philo->shared->is_running_access);
	philo->is_dead = TRUE;
}

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
// philo->time.last_meal = get_time(); // FOR EXACT TIME
void	*start_routine(void *ptr)
{
	t_philo	*philo;

	if (ptr == NULL)
		return (NULL);
	philo = (t_philo *)ptr;
	philo->is_dead = FALSE;
	philo->time.born_time = get_time();
	philo->time.last_meal = philo->time.born_time;
	pthread_mutex_lock(&philo->shared->read_shared);
	philo->shared->ready++;
	pthread_mutex_unlock(&philo->shared->read_shared);
	if (WAIT_EVERYONE == 1)
		waits_for_equals(&philo->shared->read_shared, &philo->shared->ready,
			&philo->rules->nb_philo);
	while (is_running(philo))
	{
		if (philo_routine(philo) == 0)
			return (NULL);
	}
	philo_died(philo);
	return (NULL);
}
