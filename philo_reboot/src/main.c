/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:45:40 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/13 14:05:54 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Main function of the program philo
 * 
 * @param argc argument count
 * @param argv array of arguments
 * @return int 0 OK, otherwise error (1)
 */
int	main(int argc, char **argv)
{
	t_const_rules rules;
	t_shared shared;
	t_philo *philo;

	if (parse_args(argc, argv, &rules) != 0)
		return (1);
	if (init_philos(rules, &shared, &philo) != 0)
	{
		printf("Erreur Init philos\n");
		return (2);
	}
	if (init_mutex(&shared, philo, rules.nb_philo) != 0)
	{
		printf("Erreur Init Mutex\n");
		return (3);
	}

	int count;

	count = 0;
	while (count < rules.nb_philo)
	{
		if (count % 2 == 0)
			(philo)[count].const_rules->nb_eat_target = 10;
		printf("id:%d %d %d %d %d %d\n", (philo)[count].id, (philo)[count].const_rules->nb_philo, (philo)[count].const_rules->time_to_die, (philo)[count].const_rules->time_to_eat, (philo)[count].const_rules->time_to_sleep, (philo)[count].const_rules->nb_eat_target);
		count++;
	}
	free_philos(philo, rules.nb_philo);
	free_shared(&shared, rules.nb_philo, 0);
	// free(philo);
	return (0);
}
