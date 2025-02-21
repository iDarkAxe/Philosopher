/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:45:40 by ppontet           #+#    #+#             */
/*   Updated: 2025/02/21 19:55:15 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int	free_philo(t_rules *rules, int count)
{
	int	i;

	if (rules->philo != NULL)
		free((void *)rules->philo);
	if (rules->forks != NULL)
		free((void *)rules->forks);
	i = 0;
	(void)count;
	// while(i < rules->nb_philo || i < count)
	// {
	// 	pthread_mutex_destroy(&rules->forks[i]);
	// 	i++;
	// }
	return (0);
}

static int	init_philo(t_rules *rules)
{
	int	i;

	rules->forks = NULL;
	rules->philo = malloc(sizeof(t_philo) * rules->nb_philo);
	if (rules->philo == NULL)
		return (1); //premier malloc
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->nb_philo);
	if (rules->forks == NULL)
		return (1); // TODO POTENTIEL CRASH DONC FREE */
	i = 0;
	while (i < rules->nb_philo)
	{
		rules->philo[i].id = i;
		rules->philo[i].eat_count = 0;
		rules->philo[i].last_eat = 0;
		rules->philo[i].nb_eat = rules->nb_eat;
		rules->philo[i].forks = 0;
		rules->philo[i].rules = rules;
		if (pthread_mutex_init(&rules->forks[i], NULL) != 0)
		{
			free_philo(rules, i); // TODO POTENTIEL CRASH DONC FREE */
			return (1);
		}
		i++;
	}
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	// usleep(100000);
	pthread_mutex_lock(&philo->rules->is_printing);
	printf("philo %d\n", philo->id);
	usleep(10);
	pthread_mutex_unlock(&philo->rules->is_printing);
	pthread_detach(philo->philosopher);
	// usleep(100000);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_rules	rules;

	if (argc < 5 || argc > 6)
	{
		write(2, "Error:\nWrong number of arguments\n", 33);
		return (1);
	}
	if (parse_args(argc, argv, &rules) != 0)
		return (1);
	if (init_philo(&rules) != 0)
	{
		write(2, "Error:\nCreation of rules\n", 25);
		free_philo(&rules, rules.nb_philo);
		return (1);
	}
	int i;
	pthread_mutex_init(&rules.is_printing, NULL);
	i = 0;
	while (i < rules.nb_philo)
	{
		if (pthread_create(&rules.philo[i].philosopher, NULL, &philo_routine, &rules.philo[i]) != 0)
		{
			free_philo(&rules, rules.nb_philo);
			write(2, "Error pthread_create\n", 22);
			return (1);
		}
		i++;
	}
	usleep(651006);
	free_philo(&rules, rules.nb_philo);
	return (0);
}
