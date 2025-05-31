/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:45:40 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/31 12:12:28 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_time.h"
#include "philo.h"
#include "routine.h"
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
	t_rules		rules;
	t_shared	shared;
	t_philo		*philo;

	if (parse_args(argc, argv, &rules) != 0)
		return (1);
	if (init_fx(&rules, &shared, &philo) != 0)
		return (1);
	if (rules.nb_philo == 1)
		thread_createone(&rules, &shared, philo);
	else
		thread_create(&rules, &shared, philo);
	if (rules.nb_philo == 1)
		;
	else if (rules.nb_eat_target == -1)
		observer_task(&rules, philo);
	else
		observer_task_eat(&rules, philo);
	thread_join(&rules, philo);
	if (ALL_ATE_MSG == 1)
		print_eat(philo);
	free_philos(philo);
	free_shared(&shared, rules.nb_philo, 0);
	return (0);
}
