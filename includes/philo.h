/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrabows <fgrabows@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:12:36 by fgrabows          #+#    #+#             */
/*   Updated: 2024/12/08 20:46:04 by fgrabows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*LIBRARIES*/
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>
# include <stdbool.h>
# include <errno.h>
/*VARIABLES*/

typedef pthread_mutex_t	t_mtx;
typedef struct timeval	t_tmv;
typedef enum e_optype	t_optype;
typedef struct s_philo	t_philo;

enum e_optype
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE_PHILO,
	CREATE_MONITOR,
	CREATE_ALONE,
	JOIN,
};

struct	s_data
{
	int			nr_of_threads;
	int			nr_of_philos;
	bool		dead;
	bool		error;
	long		lifetime;
	long		t_eat;
	long		t_sleep;
	long		max_meals;
	long		all_full;
	t_mtx		print;
	t_mtx		*forks;
	t_mtx		synch;
	t_mtx		full_mtx;
	t_mtx		dead_mtx;
	t_tmv		beginning;
	t_philo		*philos;
	pthread_t	monitor;
};

typedef struct s_data	t_data;

struct s_philo
{
	int			id;
	long		meal_count;
	long		meals_needed;
	bool		full;
	t_mtx		last_meal_mtx;
	t_tmv		last_meal;
	t_mtx		*r_fork_mtx;
	t_mtx		*l_fork_mtx;
	t_data		*data;
	pthread_t	philo;
	//long time_since_meal;
};

/*ERRORS*/
# define WRONG_NR_ARG \
"We need at least 4 up to 5 arguments to launch the program:v\n" \
"1. number_of philosophers\n" \
"2. time_to_die\n" \
"3. time_to_eat\n" \
"4. time_to_sleep\n" \
"5. (optional)times_each_philo_must_eat.\n" \
"Each argument should be non-negative number.\n"					

# define WRONG_TYP_ARG	"Arguments should consists only of digits\n"
# define NO_ARGS		"Lack of arguments\n"
# define EMPTY_ARG		"Empty argument\n"
# define TOO_BIG		"The max value of the agument is limited to MAX_INT\n"
# define NO_PHILO		"The number of philosophers is equal 0.\n"
# define MTX_ERR		"Error: mutex error\n"
# define PTHR_ERR		"Error: pthread error\n"
# define NO_MEM			"Error: lack of memory\n"
# define THRED_ERR		"Error: error while creating threads\n"
/*STATES*/
# define EATING		1
# define THINKING	2
# define SLEEPING	3
# define DEAD		4
/*FUNCTIONS*/
/*Xforks.c*/
void	ft_init_mutexes(t_data *data);

/*Xsafe_mutexes.c*/
int		ft_safe_mutex(t_optype type, t_mtx *mutex);

/*Xsafe_pthreads.c*/
int		ft_safe_pthread(pthread_t *thread,
			t_optype type, t_philo *philo, t_data *data);

/*Xinput_checkers.c*/
int		ft_input_manager(int argc, char **argv, t_data *data);
int		ft_isdigit(int c);

/*Xerror.c*/
int		ft_error_message(char *str);

/*Xdata_init.c*/
int		ft_data_init(t_data *data);

/*Xsafe_mutexex.c*/
int		ft_safe_mutex(t_optype type, t_mtx *mutex);

/*threads.c*/
void	ft_init_threads(int value, t_data *data);
void	*ft_philo(void *arg);
int		ft_am_i_dead(t_philo *philo);
void	*ft_monitor(void *arg);
int		ft_are_u_ok(t_philo *philo);

/*Xlocks.c*/
int		ft_print_eat(t_philo *philo, t_data *data, t_tmv cur_time, int id);
int		ft_print_fork(t_philo *philo, t_data *data, t_tmv cur_time, int id);
int		ft_print_sleep(t_philo *philo, t_data *data, t_tmv cur_time, int id);
int		ft_print_died(t_philo *philo, t_data *data, t_tmv cur_time, int id);
int		ft_print_think(t_philo *philo, t_data *data, t_tmv cur_time, int id);

/*Xeating.c*/
int		ft_get_forks(t_philo *philo);

/*Xget_time.c*/
long	ft_get_diff(t_tmv beginning, t_tmv end);
long	ft_get_sec_diff(t_tmv beginning, t_tmv end);
long	ft_get_usec_diff(t_tmv beginning, t_tmv end);
long	ft_get_msec(t_tmv start, t_tmv end);

/*Xfree_resources.c*/
int		ft_free_resources(t_data *data);
void	ft_wait_threads(t_data *data);
void	*ft_philo_alone(void *arg);
/*monitor.c*/
int		ft_am_full(t_philo *philo);
/*sleep.c*/
void	ft_after_sleep(t_philo *philo, t_data *data);
int		ft_sleep(t_philo *philo, t_tmv begining);

#endif