/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 17:53:27 by ppontet           #+#    #+#             */
/*   Updated: 2025/02/22 17:58:50 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	are_all_threads_dead(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		if (rules->philo[i].living_state != DEAD)
			return (0);
		i++;
	}
	printf("All philos are dead\n");
	return (1);
}

int	thread_creation(t_rules *rules)
{
	int		i;

	i = 0;
	while (i < rules->nb_philo)
	{
		if (pthread_create(&rules->philo[i].philosopher, NULL, &philo_routine,
				&rules->philo[i]) != 0)
		{
			free_philo(rules, rules->nb_philo);
			write(2, "Error pthread_create\n", 22);
			return (1);
		}
		pthread_detach(rules->philo[i].philosopher);
		i++;
		rules->is_everyone_ready++;
	}
	return (0);
}
