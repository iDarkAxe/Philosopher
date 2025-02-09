/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 21:24:11 by ppontet           #+#    #+#             */
/*   Updated: 2025/02/09 12:02:09 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
//! @TODO: remove this include and printf
#include <stdio.h>

static char	verify_char(char letter);
static int	verify_arguments(int argc, char **argv);
static int	ft_atoi(const char *nptr);

int	parse_args(int argc, char **argv, t_philo *philo)
{
	(void)argc;
	(void)argv;
	if (verify_arguments(argc, argv) == -1)
	{
		write(2, "Error:\nWrong arguments\n", 24);
		return (1);
	}
	philo->nb_philo = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->nb_eat = ft_atoi(argv[5]);
	else
		philo->nb_eat = 0;
	if (philo->nb_philo <= 0 || philo->time_to_die <= 0
		|| philo->time_to_eat <= 0 || philo->time_to_sleep <= 0
		|| philo->nb_eat < 0)
	{
		write(2, "Error:\nInvalid Arguments\n", 25);
		return (1);
	}
	printf("nb_philo: %zu\ntime_to_die: %d\ntime_to_eat:\
		%d\ntime_to_sleep:%d\nnb_eat: %d\n", philo->nb_philo, \
		philo->time_to_die, philo->time_to_eat, philo->time_to_sleep, \
		philo->nb_eat);
	return (0);
}

/**
 * @brief Verify if a single character is unauthorized
 *
 * @param letter character tested
 * @return char letter if authorized, 0 if not
 */
static char	verify_char(char letter)
{
	if ((letter >= '0' && letter <= '9') || letter == ' ' || letter == '+')
		return (letter);
	return (0);
}

/**
 * @brief Verify is there are unauthorized characters in arguments
 *
 * @param argc number of args
 * @param argv array of strings
 * @return int 0 if OK, -1 is error
 */
static int	verify_arguments(int argc, char **argv)
{
	size_t	index;
	int		arg_index;

	arg_index = 1;
	while (arg_index < argc)
	{
		index = 0;
		while (argv[arg_index][index] != '\0')
		{
			if (verify_char(argv[arg_index][index]) == 0)
				return (-1);
			index++;
		}
		arg_index++;
	}
	return (0);
}

/**
 * @brief Convert string to int, and handle number
 * (compliant to real atoi)
 *
 * @param nptr pointer to the start of the string
 * @return int value that was calculated
 */
static int	ft_atoi(const char *nptr)
{
	int			number;
	short int	minus_sign;

	number = 0;
	minus_sign = 0;
	while (*nptr != '\0' && (*nptr == ' ' || *nptr == '\t' || *nptr == '\n'
			|| *nptr == '\r' || *nptr == '\v' || *nptr == '\f'))
		nptr++;
	if (*nptr != '\0' && ((*nptr == '-') || (*nptr == '+')))
	{
		if (*nptr == '-')
			minus_sign = -1;
		nptr++;
	}
	while (*nptr != '\0' && *nptr >= '0' && *nptr <= '9')
		number = number * 10 + *nptr++ - '0';
	if (minus_sign == -1)
		return ((int)-number);
	return ((int)number);
}
