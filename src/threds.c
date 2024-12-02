/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrabows <fgrabows@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:29:56 by fgrabows          #+#    #+#             */
/*   Updated: 2024/11/25 15:08:32 by fgrabows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_init_threads(int nr_of_philos, t_data *data)
{
	int i;
	
	i = 0;
	ft_safe_mutex(LOCK, &data->synch);
	while(i < nr_of_philos)
	{
		ft_safe_pthread(&(data->philos[i].philo), CREATE_PHILO, &(data->philos[i]), NULL);
		i++;
	}
	ft_safe_pthread(&data->monitor, CREATE_MONITOR, NULL, data);
	i = 0;
	gettimeofday(&data->beginning, NULL);
	while(i < nr_of_philos)
	{
		ft_safe_mutex(LOCK, &(data->philos[i].last_meal_mtx));
		data->philos[i].last_meal.tv_sec = data->beginning.tv_sec;
		data->philos[i].last_meal.tv_usec =  data->beginning.tv_usec;
		ft_safe_mutex(UNLOCK, &(data->philos[i].last_meal_mtx));
		i++;
	}
	ft_safe_mutex(UNLOCK, &data->synch);
	return(0);
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
void *ft_monitor(void *arg)
{
	t_data *data;
	int status;
	int i;
	int all_full;

	data = (t_data *)arg;
	ft_safe_mutex(LOCK, &data->synch);
	ft_safe_mutex(UNLOCK, &data->synch);
	i = 0;
	while(1)
	{
		while(i < data->nr_of_philos)
		{
			if (ft_are_u_ok(&(data->philos[i]), &all_full) == 1)
				return (NULL);
			if(all_full == data->nr_of_philos)
			{
				ft_safe_mutex(LOCK, &(data->dead_mtx));
				data->dead = true;
				ft_safe_mutex(UNLOCK, &(data->dead_mtx));
			}
			i++;
		}
		all_full = 0;
		usleep(1000);
		i = 0;
	}
	return (NULL);
}

int ft_are_u_ok(t_philo *philo, int *all_full)
{
	t_tmv cur;
	int ret;

	ret = 0;
	ft_safe_mutex(LOCK, &(philo->last_meal_mtx));
	gettimeofday(&cur, NULL);
	if (ft_get_msec(philo->last_meal, cur) > philo->data->lifetime)
	{
		ft_safe_mutex(UNLOCK, &(philo->last_meal_mtx));
		ft_safe_mutex(LOCK, &(philo->data->dead_mtx));
		philo->data->dead = true;
		ft_safe_mutex(UNLOCK, &(philo->data->dead_mtx));
		ft_print_died(philo, philo->data, cur, philo->id);
		return(1);
	}
	ft_safe_mutex(UNLOCK, &(philo->last_meal_mtx));
	ft_safe_mutex(LOCK, &(philo->data->full_mtx));
	if(philo->data->all_full == philo->data->max_meals)
	{
		ft_safe_mutex(UNLOCK, &(philo->data->full_mtx));
		ft_safe_mutex(LOCK, &(philo->data->dead_mtx));
		philo->data->dead = true;
		ft_safe_mutex(UNLOCK, &(philo->data->dead_mtx));
		return (1);
	}
	ft_safe_mutex(UNLOCK, &(philo->data->full_mtx));
	return (0);
}
