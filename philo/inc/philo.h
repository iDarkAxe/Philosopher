/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 21:24:46 by ppontet           #+#    #+#             */
/*   Updated: 2025/03/13 11:52:45 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

enum					e_living_state
{
	NOT_STARTED = 0,
	LIVING = 1,
	DIED = -1,
	TAKE_FORK = 2,
	EATING = 3,
	SLEEPING = 4,
	THINKING = 5
};

typedef struct timeval	t_timeval;

typedef struct s_rules	t_rules;
typedef struct s_philo
{
	t_rules				*rules;
	int					id;
	pthread_t			philosopher;
	enum e_living_state	living_state;
	int					nb_eat;
	int					forks;
	int					*eat_count;
	int					*last_eat;
}						t_philo;

struct					s_rules
{
	int					nb_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_eat;
	t_philo				*philo;
	pthread_mutex_t		*forks;
	t_timeval			time_at_start;	
	pthread_mutex_t		is_printing;
	int					is_everyone_ready;
};

t_timeval				getdeltatime(struct timeval start_time);
void					*ft_calloc(size_t element_count, size_t element_size);

// PARSER
int						parse_args(int argc, char **argv, t_rules *rules);

// PHILO
int						init_philo(t_rules *rules);
void					*philo_routine(void *arg);
int						free_philo(t_rules *rules, int count);

// THREAD
int						are_all_threads_dead(t_rules *rules);
int						are_all_threads_state(t_rules *rules,
							enum e_living_state state);
int						thread_creation(t_rules *rules);

#endif
