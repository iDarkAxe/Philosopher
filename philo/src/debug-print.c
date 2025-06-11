/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug-print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:07:38 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/11 10:07:13 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <fcntl.h>
#include "ft_time.h"

/**
 * @brief Just prints the number of times each philosopher has eaten
 * 
 * @param philo philosopher structure
 */
void	print_eat(t_philo *philo)
{
	int	count;

	if (philo == NULL)
		return ;
	count = 0;
	while (count < philo->rules->nb_philo)
	{
		dprintf(2, "philo %d has eaten %d times\n", philo[count].id,
			philo[count].nb_eat);
		count++;
	}
}

void	print_timings(t_philo *philo, int count, struct timeval timer,
		struct timeval limit)
{
	if (philo == NULL)
	{
		write(2, "print_timings : NULL pointer\n", 29);
		return ;
	}
	dprintf(2, "Philo %d\n", philo[count].id);
	dprintf(2, "- last_meal:\t%ld.%06ld \n", philo[count].time.last_meal.tv_sec,
		philo[count].time.last_meal.tv_usec);
	dprintf(2, "- now:\t\t%ld.%06ld \n", timer.tv_sec, timer.tv_usec);
	dprintf(2, "- limit:\t\t%ld.%06ld \n", limit.tv_sec, limit.tv_usec);
	dprintf(2, "result is %d\n", compare_time(&timer, &limit));
}

// void	print_timings_fd(t_philo *philo, int count, struct timeval timer,
// 		struct timeval limit)
// {
// 	static int	fd = -1;

// 	if (fd == -1)
// 		fd = open("log.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	dprintf(fd, "Philo %d\n", philo[count].id);
// 	dprintf(2, "- last_meal:\t%ld.%06ld \n", philo[count].time.last_meal.tv_sec,
// 		philo[count].time.last_meal.tv_usec);
// 	dprintf(2, "- now:\t\t%ld.%06ld \n", timer.tv_sec, timer.tv_usec);
// 	dprintf(2, "- limit:\t\t%ld.%06ld \n", limit.tv_sec, limit.tv_usec);
// 	dprintf(fd, "result is %d\n", compare_time(&timer, &limit));
// }
