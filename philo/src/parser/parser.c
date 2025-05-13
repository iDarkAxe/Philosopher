/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 21:24:11 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/13 12:47:23 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	verify_char(char letter);
static int	verify_arguments(int argc, char **argv);
static int	ft_atoi(const char *nptr);

/**
 * @brief Parse arguments and store them in the rules structure
 * Uses simple atoi function to convert strings to int
 *
 * @param argc number of arguments
 * @param argv array of strings
 * @param rules pointer to the rules structure
 * @return int 0 if OK, 1 if error
 */
int	parse_args(int argc, char **argv, t_rules *rules)
{
	if (argc < 5 || argc > 6)
	{
		error_message(NBR_OF_ARGUMENT_INVALID);
		return (1);
	}
	if (verify_arguments(argc, argv) == -1)
		return (2);
	rules->nb_philo = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		rules->nb_eat_target = ft_atoi(argv[5]);
	else
		rules->nb_eat_target = -1;
	if (rules->nb_philo <= 0 || rules->nb_philo > 400
		|| rules->time_to_die <= 0 || rules->time_to_eat <= 0
		|| rules->time_to_sleep <= 0 || rules->nb_eat_target < -1)
	{
		error_message(ARGUMENT_INVALID);
		return (3);
	}
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
			{
				error_message(WRONG_ARGUMENT);
				return (-1);
			}
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
