/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 21:24:46 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/13 17:16:00 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

# ifndef DEBUG
#  define DEBUG 0
# endif

enum							e_error_message
{
	ARGUMENT_INVALID = -1,
	WRONG_ARGUMENT = 0,
	TOO_MUCH_PHILOS = 1,
	NBR_OF_ARGUMENT_INVALID = 2,
	RULES_NOT_CREATED = 3,
	PTHREAD_CREATING = 4,
	PTHREAD_DETACH = 5
};

enum							e_bool
{
	TRUE = 1,
	FALSE = 0
};

typedef struct s_const_rules	t_const_rules;
typedef struct s_philo			t_philo;
typedef struct s_shared			t_shared;

struct							s_const_rules
{
	int							nb_philo;
	int							time_to_die;
	int							time_to_eat;
	int							time_to_sleep;
	int							nb_eat_target;
};

struct							s_philo
{
	const t_const_rules			*const_rules;
	t_shared					*shared;
	pthread_t					philosopher;
	int							id;
	int							nb_eat;
	int							state;
};

struct							s_shared
{
	int							ready;
	enum e_bool					*forks_nbr;
	pthread_mutex_t				*forks;
	pthread_mutex_t				print;
	pthread_mutex_t				read_shared;
};

/*
struct							s_philo
{
	const t_const_rules			*rules;
	t_shared					*shared;
	t_timeval					time_at_wakeup;
	enum e_living_state			living_state;
	int							nb_eat;
	int							forks;
	int							*eat_count;
	int							*last_eat;
};
*/

// Parsing
int								parse_args(int argc, char **argv,
									t_const_rules *rules);

// Init
int								init_philos(t_const_rules *rules,
									t_shared *shared, t_philo **philo);
// int init_forks_mutex(t_shared *shared, int count);
int								init_mutex(t_shared *shared, t_philo *philo,
									int count);

// Free
void							free_shared(t_shared *shared, int count,
									int flag);
void							free_philos(t_philo *philo, int count);

// Utils
void							*ft_calloc(size_t element_count,
									size_t element_size);
void							ft_bzero(void *s, size_t n);
void							*ft_memcpy(void *destination,
									const void *source, size_t size);

// Error handling
ssize_t							error_message(enum e_error_message state);

#endif
