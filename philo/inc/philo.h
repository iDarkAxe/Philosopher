/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 21:24:46 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/31 13:21:34 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/**
 * @file philo.h
 * @brief Header file for the philosopher's project.
 *
 * Contains all structures, function prototypes,
 *	and constants used in the project.
 */

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

# ifndef ALL_ATE_MSG
#  define ALL_ATE_MSG 0
# endif

/**
 * @defgroup Structures Structures for managing the philosophers
 * @brief Structures to manipulate the philosophers and their states.
 * @{
 */

/**
 * @brief Delay for the usleep function
 *
 * Best values seems to be 50ms-1000ms with 100 philosophers
 * 500ms is a good value overall as it don't overload
 * the CPU too much with context switching
 */
# ifndef DELAY
#  define DELAY 500
# endif

/**
 * @brief Macro to make all the philosophers wait starting simultaneously
 *
 */
# ifndef WAIT_EVERYONE
#  define WAIT_EVERYONE 0
# endif

/**
 * @brief Error codes for the program
 *
 */
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

/**
 * @brief Error messages for the program
 *
 */
# define NBR_OF_ARGUMENT_INVALID_MSG "Error:\nWrong number of arguments\n"
# define ARGUMENT_INVALID_MSG \
	"Values accepted :\n\tnb_philo 0-400\n\
	die_time > 0\n\teat_time > 0\n\tsleep_time > 0\n\tnb_eat \t>= 0\n"
# define WRONG_ARGUMENT_MSG "Error:\nArguments should be only integers\n"
# define TOO_MUCH_PHILOS_MSG "Error:\nToo much philos, should be under 400\n"
# define RULES_NOT_CREATED_MSG "Error:\nCreation of rules\n"
# define PTHREAD_CREATING_MSG "Error pthread_create\n"
# define PTHREAD_DETACH_MSG "Error pthread_detach\n"

/**
 * @brief State of the philosopher
 *
 */
enum					e_philo_state
{
	TOOK_FORK = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	DIED = 4
};

typedef struct s_rules	t_rules;
typedef struct s_philo	t_philo;
typedef struct s_shared	t_shared;
typedef struct s_time	t_time;

struct					s_time
{
	struct timeval	last_meal; /**< Time of the last meal*/
	struct timeval	born_time; /**< Time when philo started*/
};

struct					s_rules
{
	struct timeval	start;			/**< Time of the start of the simulation*/
	int				nb_philo;
	int				time_to_die;	/**< Time before dying*/
	int				time_to_eat;	/**< Time took for eating*/
	int				time_to_sleep;	/**< Time took for sleeping*/
	int				nb_eat_target;	/**< Nbr of time each philo should eat*/
};

struct					s_philo
{
	const t_rules	*rules;			/**<	Rules of the simulation*/
	t_shared		*shared;		/**< Ptr to Shared data between philos*/
	// pthread_mutex_t	mutex_nb_eat;	/**< Mutex to access last meal*/
	pthread_t		philosopher;	/**< Philosopher thread*/
	t_time			time;			/**< Time of the philosopher*/
	int				id;				/**< Philosopher ID*/
	int				nb_eat;			/**< Nbr of time the philosopher has eaten*/
};

struct					s_shared
{
	pthread_mutex_t	mutex_nb_eat;		/**< Mutex to access last meal*/
	pthread_mutex_t	mutex_ready;		/**< Mutex to access shared data*/
	pthread_mutex_t	mutex_is_running;	/**< Mutex to access is_running*/
	pthread_mutex_t	mutex_printing;		/**< Mutex to have access to printing*/
	pthread_mutex_t	*forks;				/**< Forks mutex*/
	char			*is_fork_taken;		/**< Forks state*/
	int				ready;				/**< Flag to check if philos are ready*/
	char			is_running;			/**< Flag to check if sim is running*/
};
/** @} */

/**
 * @defgroup Functions Functions for the philosopher's project
 * @brief Function used by the observer of philosophers
 * @{
 */
// Parsing
int						parse_args(int argc, char **argv, t_rules *rules);

// Preparation
int						init_fx(t_rules *rules, t_shared *shared,
							t_philo **philo);
int						is_sim_running(t_philo *philo);

// Thread
int						thread_create(t_rules *rules, t_shared *shared,
							t_philo *philo);
int						thread_join(t_rules *rules, t_philo *philo);
int						thread_createone(t_rules *rules, t_shared *shared,
							t_philo *philo);

// Observer
void					observer_task(const t_rules *rules, t_philo *philo);
void					observer_task_eat(const t_rules *rules, t_philo *philo);

// Free
void					free_shared(t_shared *shared, int count, int flag);
void					free_philos(t_philo *philo);

// Error handling
ssize_t					error_message(enum e_error_message state);

// Debug print
void					print_eat(t_philo *philo);
void					print_timings(t_philo *philo, int count,
							struct timeval timer, struct timeval limit);
// void					print_timings_fd(t_philo *philo, int count,
// 							struct timeval timer, struct timeval limit);

// Utils
void					*ft_calloc(size_t element_count, size_t element_size);
void					ft_bzero(void *s, size_t n);
void					*ft_memcpy(void *destination, const void *source,
							size_t size);
size_t					ft_strlen(const char *str);
/** @} */

#endif
