/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 12:06:21 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/12 12:23:11 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

ssize_t	error_message(enum e_error_message state)
{
	if (state == NBR_OF_ARGUMENT_INVALID)
		return (write(2, "Error:\nWrong number of arguments\n", 33));
	else if (state == TOO_MUCH_PHILOS)
		return (write(2, "Error:\nToo much philos, should be under 400\n", 44));
	else if (state == WRONG_ARGUMENT)
		return (write(2, "Error:\nArguments should be only integers\n", 41));
	else if (state == ARGUMENT_INVALID)
		return (write(2, "Error:\nInvalid Arguments\n", 25));
	else if (state == RULES_NOT_CREATED)
		return (write(2, "Error:\nCreation of rules\n", 25));
	else if (state == PTHREAD_DETACH)
		return (write(2, "Error pthread_detach\n", 21));
	else if (state == PTHREAD_CREATING)
		return (write(2, "Error pthread_create\n", 21));
	return (0);
}
