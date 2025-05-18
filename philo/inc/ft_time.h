/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:46:44 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/18 13:41:12 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TIME_H
# define FT_TIME_H

# include "philo.h"

/**
 * @defgroup Time Functions for the philosopher's timings
 * @brief Function used by philos to manage their timings
 * @{
 */
struct timeval	get_time(void);
struct timeval	get_dtime(t_philo *philo);
void			ft_usleep(__useconds_t wait_time, t_philo *philo);
int				compare_time(struct timeval *t1, struct timeval *t2);
struct timeval	*add_ms_timeval(struct timeval *tv, long milliseconds);
void			wait_everyone(t_philo *philo, const int *const value1,
					const int *const value2);
int				does_not_have_time(t_philo *philo, enum e_philo_state p_state);
/** @} */

#endif
