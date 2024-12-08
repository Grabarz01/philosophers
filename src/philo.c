/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_alone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrabows <fgrabows@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 10:51:30 by fgrabows          #+#    #+#             */
/*   Updated: 2024/12/08 19:23:15 by fgrabows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	*ft_philo_alone(void *arg)
{
	t_philo	*philo;
	t_tmv	time;

	philo = (t_philo *)arg;
	ft_safe_mutex(LOCK, &philo->data->synch);
	ft_safe_mutex(UNLOCK, &philo->data->synch);
	ft_safe_mutex(LOCK, philo->l_fork_mtx);
	ft_print_fork(philo, philo->data, time, philo->id);
	ft_safe_mutex(UNLOCK, philo->l_fork_mtx);
	return (NULL);
}


void *ft_philo(void *arg)
{
	t_philo *philo;
	int status;
	
	philo = (t_philo *)arg;
	ft_safe_mutex(LOCK, &philo->data->synch);
	ft_safe_mutex(UNLOCK, &philo->data->synch);
	if(philo->id % 2 == 0)
		usleep(1000);
	while(1)
	{
		if (ft_am_i_dead(philo) == 1)
			return (NULL);
		if (ft_get_forks(philo) == 1)
			return (NULL);
	}
}

int ft_am_i_dead(t_philo *philo)
{
	int ret;
	
	ft_safe_mutex(LOCK, &(philo->data->dead_mtx));
	ret = (int)philo->data->dead;
	ft_safe_mutex(UNLOCK, &(philo->data->dead_mtx));
	return(ret);
}
