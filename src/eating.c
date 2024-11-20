/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrabows <fgrabows@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:44:53 by fgrabows          #+#    #+#             */
/*   Updated: 2024/11/18 19:50:03 by fgrabows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void ft_after_sleep(t_philo *philo, t_data *data);
static int ft_sleep(t_philo *philo, t_tmv begining);
static int ft_odd_philo(t_philo *philo, int id);
static int ft_even_philo(t_philo *philo, int id);
static void ft_forks_taken(t_philo *philo, t_tmv *tmp);

int ft_get_forks(t_philo *philo)
{
	if (ft_am_i_dead(philo) == 1)
		return (1);
	if(philo->id % 2 == 0)
	{	
		if (ft_even_philo(philo, philo->id) == 1)
			return (1);
	}
	else 
	{
		if (ft_odd_philo(philo, philo->id) == 1)
			return (1);
	}
	if (ft_am_i_dead(philo) == 1)
		return (1);
	ft_after_sleep(philo, philo->data);
}

static int ft_odd_philo(t_philo *philo, int id)
{
	t_tmv tmp;
	
	ft_safe_mutex(LOCK, philo->l_fork_mtx);
	ft_safe_mutex(LOCK, philo->r_fork_mtx);
	if(ft_are_u_ok(philo) == 1)
		return(1);
	ft_forks_taken(philo, &tmp);
	ft_my_usleep(philo->data->t_eat * 1000, tmp);
	ft_safe_mutex(UNLOCK, philo->l_fork_mtx);
	ft_safe_mutex(UNLOCK, philo->r_fork_mtx);
	gettimeofday(&tmp, NULL);
	if(ft_are_u_ok(philo) == 1)
		return(1);
	ft_lock_prinft(SLEEPING, philo->data, tmp, philo->id);
	ft_sleep(philo, tmp);
}

static int ft_even_philo(t_philo *philo, int id)
{
	t_tmv tmp;

	ft_safe_mutex(LOCK, philo->r_fork_mtx);
	ft_safe_mutex(LOCK, philo->l_fork_mtx);
	if(ft_are_u_ok(philo) == 1)
		return(1);
	ft_forks_taken(philo, &tmp);
	ft_safe_mutex(UNLOCK, philo->r_fork_mtx);
	ft_safe_mutex(UNLOCK, philo->l_fork_mtx);
	ft_my_usleep(philo->data->t_eat * 1000, tmp);
	gettimeofday(&tmp, NULL);
	if(ft_am_i_dead(philo) == 1)
		return(1);
	ft_lock_prinft(SLEEPING, philo->data, tmp, philo->id);
	if (ft_sleep(philo, tmp) == 1)
		return (1);
}

static void ft_forks_taken(t_philo *philo, t_tmv *tmp)
{
	ft_safe_mutex(LOCK, &philo->last_meal_mtx);
	gettimeofday(&philo->last_meal, NULL);
	tmp->tv_sec = philo->last_meal.tv_sec;
	tmp->tv_usec = philo->last_meal.tv_usec;
	ft_safe_mutex(UNLOCK, &philo->last_meal_mtx);
	ft_lock_prinft(EATING, philo->data, *tmp, philo->id);
}

static int ft_sleep(t_philo *philo, t_tmv begining)
{
	t_tmv timer;
	
	ft_my_usleep(philo->data->t_sleep * 1000, begining);
	if(ft_are_u_ok(philo) == 1)
		return(1);
	gettimeofday(&timer, NULL);
	ft_lock_prinft(THINKING, philo->data, timer, philo->id);

}

static void ft_after_sleep(t_philo *philo, t_data *data)
{
	int philo_nr;
	long time_to_think;

	philo_nr = philo->data->nr_of_philos;
	time_to_think = data->t_eat * 2 - data->t_sleep * 2;
	if(philo_nr % 2 == 0)
		usleep(1000);
	else
	{ 
		if (time_to_think > 0)
		{
			usleep(time_to_think * 1000);
		}
		else 
		{
			usleep(1000);
		}
	}
}
//t_eat t_sleep
// I eating II waiting III waiting
// I thinking/sleeping II eating III waiting
// I has to be thinking until III gets forks II eating/sleeping II eating

//eating+sleeping+thinking > eating + eating + 1
