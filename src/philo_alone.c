
#include "philo.h"

void *ft_philo_alone(void *arg)
{
    t_philo *philo;
    t_tmv time;
int ft_print_fork(t_philo *philo, t_data *data, t_tmv cur_time, int id)

    philo = (t_philo *)arg;

    ft_safe_mutex(LOCK, philo->r_fork_mtx);
    gettimeofday(&time, NULL);
    ft_print_fork(philo, philo->data, time, philo->id);
    ft_safe_mutex(UNLOCK, philo->r_fork_mtx);
    return(NULL);
}
