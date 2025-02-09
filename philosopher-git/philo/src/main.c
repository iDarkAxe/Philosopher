/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:45:40 by ppontet           #+#    #+#             */
/*   Updated: 2025/02/09 10:51:25 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (argc < 5 || argc > 6)
	{
		write(2, "Error:\nWrong number of arguments\n", 33);
		return (1);
	}
	if (parse_args(argc, argv, &philo) != 0)
		return (1);
	return (0);
}
