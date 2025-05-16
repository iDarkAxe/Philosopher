/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:46:44 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/16 12:06:57 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROUTINE_H
# define ROUTINE_H

# include "philo.h"

/**
 * @defgroup Routine Functions for the philosopher's routine
 * @brief Function used by philos to manage their routine
 * @{
 */
int						philo_routine(t_philo *philo);
void					*start_routine(void *ptr);
void					print_message(t_philo *philo,
							enum e_philo_state p_state);
int						try_taking_fork(t_philo *philo, char is_left);
int						set_back_fork(t_philo *philo, char is_left);
int						try_eating(t_philo *philo);
int						has_everyone_ate(t_philo *philo);
void					philo_died(t_philo *philo);
/** @} */

#endif
