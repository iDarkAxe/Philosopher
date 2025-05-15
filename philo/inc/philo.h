/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 21:24:46 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/15 17:40:17 by ppontet          ###   ########lyon.fr   */
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

# ifndef DELAY
#  define DELAY 500
# endif

# ifndef WAIT_EVERYONE
#  define WAIT_EVERYONE 0
# endif

enum					e_error_message
{
	NBR_OF_ARGUMENT_INVALID,
	ARGUMENT_INVALID,
	WRONG_ARGUMENT,
	TOO_MUCH_PHILOS,
	RULES_NOT_CREATED,
	PTHREAD_CREATING,
	PTHREAD_DETACH,
};

# define NBR_OF_ARGUMENT_INVALID_MSG "Error:\nWrong number of arguments\n"
# define ARGUMENT_INVALID_MSG \
	"Values accepted :\n\tnb_philo 0-400\n\
	die_time > 0\n\teat_time > 0\n\tsleep_time > 0\n\tnb_eat \t>= 0\n"
# define WRONG_ARGUMENT_MSG "Error:\nArguments should be only integers\n"
# define TOO_MUCH_PHILOS_MSG "Error:\nToo much philos, should be under 400\n"
# define RULES_NOT_CREATED_MSG "Error:\nCreation of rules\n"
# define PTHREAD_CREATING_MSG "Error pthread_create\n"
# define PTHREAD_DETACH_MSG "Error pthread_detach\n"

enum					e_philo_state
{
	TOOK_FORK = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	DIED = 4
};

enum					e_bool
{
	TRUE = 1,
	FALSE = 0
};

typedef struct s_rules	t_rules;
typedef struct s_philo	t_philo;
typedef struct s_shared	t_shared;
typedef struct s_time	t_time;

struct					s_time
{
	size_t				die;
	size_t				eat;
	size_t				sleep;
	size_t				last_meal;
	size_t				born_time;
};

struct					s_rules
{
	int					nb_philo;
	struct timeval		start;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_eat_target;
};

struct					s_philo
{
	const t_rules		*rules;
	t_shared			*shared;
	pthread_t			philosopher;
	t_time				time;
	int					id;
	int					nb_eat;
	enum e_bool			is_dead;
};

struct					s_shared
{
	int					ready;
	enum e_bool			is_running;
	enum e_bool			*forks_nbr;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print;
	pthread_mutex_t		is_running_access;
	pthread_mutex_t		meal_access;
	pthread_mutex_t		read_shared;
};

// Parsing
int						parse_args(int argc, char **argv, t_rules *rules);

// Init
int						init_philos(t_rules *rules, t_shared *shared,
							t_philo **philo);
// int init_forks_mutex(t_shared *shared, int count);
int						init_mutex(t_shared *shared, t_philo *philo, int count);

// Philo
int						philo_routine(t_philo *philo);
void					*start_routine(void *ptr);
void					print_message(t_philo *philo,
							enum e_philo_state p_state);
int						is_running(t_philo *philo);
int						try_taking_fork(t_philo *philo, char is_left);
int						set_back_fork(t_philo *philo, char is_left);
int						try_eating(t_philo *philo);
int						has_everyone_ate(t_philo *philo);
void					philo_died(t_philo *philo);

// Free
void					free_shared(t_shared *shared, int count, int flag);
void					free_philos(t_philo *philo, int count);

// Utils
void					*ft_calloc(size_t element_count, size_t element_size);
void					ft_bzero(void *s, size_t n);
void					*ft_memcpy(void *destination, const void *source,
							size_t size);
size_t					ft_strlen(const char *str);

// Time
size_t					get_time(void);
size_t					get_dtime(t_philo *philo);
void					ft_usleep(size_t wait_time, t_philo *philo);
void					waits_for_equals(pthread_mutex_t *mutex,
							const int *const value1, const int *const value2);
int						does_have_time(t_philo *philo,
							enum e_philo_state p_state);

// Error handling
ssize_t					error_message(enum e_error_message state);

// DEBUG
void					print_eat(t_philo *philo);

#endif
