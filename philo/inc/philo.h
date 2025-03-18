/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 21:24:46 by ppontet           #+#    #+#             */
/*   Updated: 2025/03/18 14:24:28 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

# ifndef DEBUG
# define DEBUG 0
# endif

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

typedef struct timeval				t_timeval;

typedef struct s_rules				t_rules;
typedef struct s_const_rules		t_const_rules;
typedef struct s_shared_ressources	t_shared_ressources;

typedef struct s_philo
{
	const t_const_rules	*rules;
	t_shared_ressources	*shared;
	t_timeval			time_at_wakeup;
	int					id;
	pthread_t			philosopher;
	enum e_living_state	living_state;
	int					nb_eat;
	int					forks;
	int					*eat_count;
	int					*last_eat;
}						t_philo;

struct					s_const_rules
{
	int					nb_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_eat;
	t_philo				*philo;
	t_timeval			time_at_start;
	int					is_everyone_ready;
};

struct s_shared_ressources
{
	pthread_mutex_t		*forks;
	pthread_mutex_t		is_printing;
};

struct s_rules
{
	t_const_rules		rules;
	t_shared_ressources	shared;
};

t_timeval				getdeltatime(struct timeval start_time);
void					*ft_calloc(size_t element_count, size_t element_size);

// PARSER
int						parse_args(int argc, char **argv, t_const_rules *rules);

// PHILO
int						init_philo(t_rules *rules);
void					*philo_routine(void *arg);
int						free_philo(t_const_rules *rules, t_shared_ressources *shared, int count);

// THREAD
int						are_all_threads_dead(const t_const_rules *rules);
int						are_all_threads_state(const t_const_rules *rules, enum e_living_state state);
int						thread_creation(t_const_rules *rules, t_shared_ressources *shared);

#endif
