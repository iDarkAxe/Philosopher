/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:45:40 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/11 16:30:32 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int			thread_manip(t_const_rules *rules, t_shared *shared,
				t_philo *philo);

int	thread_manip(t_const_rules *rules, t_shared *shared, t_philo *philo)
{
	int	count;

	count = 0;
	while (count < rules->nb_philo)
	{
		if (pthread_create(&philo[count].philosopher, NULL,
				(void *(*)(void *))start_routine, (void *)&philo[count]) != 0)
		{
			free_philos(philo, rules->nb_philo);
			free_shared(shared, rules->nb_philo, 0);
			return (1);
		}
		count++;
	}
	count = 0;
	while (count < rules->nb_philo)
	{
		pthread_join(philo[count].philosopher, NULL);
		count++;
	}
	return (0);
}

/**
 * @brief Main function of the program philo
 *
 * @param argc argument count
 * @param argv array of arguments
 * @return int 0 OK, otherwise error (1)
 */
int	main(int argc, char **argv)
{
	t_const_rules	rules;
	t_shared		shared;
	t_philo			*philo;

	if (parse_args(argc, argv, &rules) != 0)
		return (1);
	if (init_philos(&rules, &shared, &philo) != 0)
	{
		printf("Erreur Init philos\n");
		return (2);
	}
	if (init_mutex(&shared, philo, rules.nb_philo) != 0)
	{
		printf("Erreur Init Mutex\n");
		return (3);
	}
	thread_manip(&rules, &shared, philo);
	free_philos(philo, rules.nb_philo);
	free_shared(&shared, rules.nb_philo, 0);
	return (0);
}
