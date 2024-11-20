/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrabows <fgrabows@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:29:56 by fgrabows          #+#    #+#             */
/*   Updated: 2024/11/18 20:01:10 by fgrabows         ###   ########.fr       */
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
		if (ft_safe_pthread(&(data->philos[i].philo), CREATE_PHILO, &(data->philos[i]), NULL) == 1)
			return (ft_i_threads_destroy(data, i));
		i++;
	}
	if (ft_safe_pthread(&data->monitor, CREATE_MONITOR, NULL, data) == -1)
		return (ft_i_threads_destroy(data, i));
	gettimeofday(&data->beginning, NULL);
	i = 0;
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
	while(1)
	{
		status = ft_am_i_dead(philo);
		if (status == 1)
			return(NULL);
		if (ft_get_forks(philo) == 1)
			return (NULL);
	}
}

int ft_am_i_dead(t_philo *philo)
{
	int ret;
	
	ft_safe_mutex(LOCK, &(philo->data->dead_mtx));
	if (philo->data->dead == true)
		ret = 1;
	else 
		ret = 0;
	ft_safe_mutex(UNLOCK, &(philo->data->dead_mtx));
	return(ret);
}
void *ft_monitor(void *arg)
{
	t_data *data;
	bool dead;
	int status;
	int i;

	dead = false;
	i = 0;
	data = (t_data *)arg;
	while(dead == false)
	{
		while(i < data->nr_of_philos)
		{
			status = ft_are_u_ok(&(data->philos[i]));
			if (status == 1)
			{	
				dead = true;
				break;
			}	
			i++;
		}
		usleep(1000);
		i = 0;
	}
	return (NULL);
}

int ft_are_u_ok(t_philo *philo)
{
	t_tmv cur;
	int ret;

	ret = 0;
	ft_safe_mutex(LOCK, &(philo->last_meal_mtx));
	gettimeofday(&cur, NULL);
	if (ft_get_diff(philo->last_meal, cur) > philo->data->lifetime * 1000)
	{
		ft_safe_mutex(LOCK, &(philo->data->dead_mtx));
		philo->data->dead = true;
		ft_lock_prinft(DEAD, philo->data, cur, philo->id);
		ft_safe_mutex(UNLOCK, &(philo->data->dead_mtx));
		ret = 1;
	}
	ft_safe_mutex(UNLOCK, &(philo->last_meal_mtx));
	//printf("ret status %d- philo%d\n", ret, philo->id);
	return(ret);
}
