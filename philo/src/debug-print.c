/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug-print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:07:38 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/13 13:11:43 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	print_eat(t_philo *philo)
{
	int	count;

	if (philo == NULL)
		return ;
	count = 0;
	while (count < philo->rules->nb_philo)
	{
		printf("philo %d has eaten %d times\n", philo[count].id,
			philo[count].nb_eat);
		count++;
	}
}
