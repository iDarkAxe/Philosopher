/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 12:06:21 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/16 12:34:25 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Function to print the error message
 * 
 * @param state error message state
 * @return ssize_t number of bytes written
 */
ssize_t	error_message(enum e_error_message state)
{
	static const char	*msg[] = {NBR_OF_ARGUMENT_INVALID_MSG,
		ARGUMENT_INVALID_MSG, WRONG_ARGUMENT_MSG, TOO_MUCH_PHILOS_MSG,
		RULES_NOT_CREATED_MSG, PTHREAD_CREATING_MSG, PTHREAD_DETACH_MSG};

	return (write(2, msg[(int)state], ft_strlen(msg[(int)state])));
}
