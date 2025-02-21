/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 21:24:46 by ppontet           #+#    #+#             */
/*   Updated: 2025/02/21 19:48:38 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>

typedef struct timeval	t_timeval;

typedef struct s_rules t_rules;
typedef struct s_philo
{
	t_rules *rules;
	int id;
	pthread_t		philosopher;
	int				nb_eat;
	int				forks;
	int				*eat_count;
	int				*last_eat;
}	t_philo;

struct s_rules
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t is_printing;
};

int	parse_args(int argc, char **argv, t_rules *rules);

#endif
