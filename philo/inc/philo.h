/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 21:24:46 by ppontet           #+#    #+#             */
/*   Updated: 2025/02/09 10:50:15 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>

typedef struct timeval	t_timeval;

typedef struct s_philo
{
	int				id;
	size_t			nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
	int				*forks;
	int				*eat_count;
	int				*last_eat;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*eat_mutex;
}	t_philo;

int	parse_args(int argc, char **argv, t_philo *philo);

#endif
