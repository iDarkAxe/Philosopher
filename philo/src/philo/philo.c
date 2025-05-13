/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 17:56:02 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/13 13:06:43 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// TAKE A LEFT FORK
// pthread_mutex_lock(&philo->shared->forks[philo->id]);
// TAKE A RIGHT FORK
// pthread_mutex_lock(&philo->shared->forks[(philo->id + 1)
// % philo->rules->nb_philo]);

void	philo_routine(t_philo *philo)
{
	if (philo == NULL)
		return ;
	print_message(philo, THINKING);
	does_have_time(philo, TOOK_FORK);
	pthread_mutex_lock(&philo->shared->forks[philo->id]);
	print_message(philo, TOOK_FORK);
	pthread_mutex_lock(&philo->shared->forks[(philo->id + 1)
		% philo->rules->nb_philo]);
	print_message(philo, TOOK_FORK);
	pthread_mutex_lock(&philo->shared->meal_access);
	print_message(philo, EATING);
	philo->time.last_meal = get_time();
	philo->nb_eat += 1;
	pthread_mutex_unlock(&philo->shared->forks[(philo->id + 1)
		% philo->rules->nb_philo]);
	pthread_mutex_unlock(&philo->shared->forks[philo->id]);
	pthread_mutex_unlock(&philo->shared->meal_access);
	ft_usleep(philo->rules->time_to_eat);
	print_message(philo, SLEEPING);
	ft_usleep(philo->rules->time_to_sleep);
}
int		has_everyone_ate(t_philo *philo);

// TO desynchronise even philos
// if (philo->id % 2 == 0)
// 	ft_usleep(1);
// philo->time.last_meal = get_time(); // FOR EXACT TIME
void	*start_routine(void *ptr)
{
	t_philo	*philo;
	size_t	index;

	if (ptr == NULL)
		return (NULL);
	philo = (t_philo *)ptr;
	philo->time.born_time = get_time();
	philo->time.last_meal = philo->time.born_time;
	pthread_mutex_lock(&philo->shared->read_shared);
	philo->shared->ready++;
	pthread_mutex_unlock(&philo->shared->read_shared);
	if (WAIT_EVERYONE == 1)
		waits_for_equals(&philo->shared->read_shared, &philo->shared->ready,
			&philo->rules->nb_philo);
	index = 0;
	while (index < 10 && is_running(philo) && has_everyone_ate(philo) == 0)
	{
		philo_routine(philo);
		index++;
	}
	return (NULL);
}
