/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:45:40 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/20 13:08:53 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_time.h"
#include "philo.h"
#include "routine.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>

void		print_nul(t_philo *philo, int count, struct timeval timer,
				struct timeval limit);

void	print_nul(t_philo *philo, int count, struct timeval timer,
		struct timeval limit)
{
	static int	fd = -1;

	if (fd == -1)
		fd = open("log.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	dprintf(fd, "Philo %d\n", philo[count].id);
	dprintf(2, "- last_meal:\t%ld.%06ld \n", philo[count].time.last_meal.tv_sec,
		philo[count].time.last_meal.tv_usec);
	dprintf(2, "- now:\t\t%ld.%06ld \n", timer.tv_sec, timer.tv_usec);
	dprintf(2, "- limit:\t\t%ld.%06ld \n", limit.tv_sec, limit.tv_usec);
	dprintf(fd, "result is %d\n", compare_time(&timer, &limit));
}

static void	observer_task(const t_rules *rules, t_philo *philo);
static void	observer_task_eat(const t_rules *rules, t_philo *philo);

/**
 * @brief Function to observe the philos
 *
 * @param philo head of philosopher structure
 */
static void	observer_task(const t_rules *rules, t_philo *philo)
{
	struct timeval	timer;
	struct timeval	limit;
	int				count;

	count = 0;
	while (is_sim_running(philo) == 1)
	{
		if (count >= rules->nb_philo)
			count = 0;
		pthread_mutex_lock(&philo[count].mutex_nb_eat);
		timer = get_time();
		timer.tv_sec -= philo[count].time.born_time.tv_sec;
		timer.tv_usec -= philo[count].time.born_time.tv_usec;
		limit = philo[count].time.last_meal;
		add_ms_timeval(&limit, rules->time_to_die);
		if (compare_time(&timer, &limit) == 1)
			philo_died(philo);
		pthread_mutex_unlock(&philo[count].mutex_nb_eat);
		count++;
	}
}

/**
 * @brief Function to observe the philos
 *
 * @param philo head of philosopher structure
 */
static void	observer_task_eat(const t_rules *rules, t_philo *philo)
{
	struct timeval	timer;
	struct timeval	limit;
	int				count;

	count = 0;
	while (is_sim_running(philo) == 1)
	{
		if (count >= rules->nb_philo)
			count = 0;
		pthread_mutex_lock(&philo[count].mutex_nb_eat);
		timer = get_time();
		limit = philo[count].time.last_meal;
		add_ms_timeval(&limit, rules->time_to_die);
		if (compare_time(&timer, &limit) == 1)
			philo_died(philo);
		pthread_mutex_unlock(&philo[count].mutex_nb_eat);
		count++;
		if (has_everyone_ate(philo) == 1)
		{
			pthread_mutex_lock(&philo->shared->mutex_is_running);
			philo->shared->is_running = 0;
			pthread_mutex_unlock(&philo->shared->mutex_is_running);
			break ;
		}
	}
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
