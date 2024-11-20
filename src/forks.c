/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrabows <fgrabows@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:13:15 by fgrabows          #+#    #+#             */
/*   Updated: 2024/11/18 17:47:24 by fgrabows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void ft_assign_forks(t_data *data);
static void ft_assign_mtx(t_philo *philo, int i, t_data *data);

int ft_init_mutexes(t_data *data)
{
	int i;
	
	i = 0;
	while (i < data->nr_of_philos)
	{
		if (ft_safe_mutex(INIT, &(data->forks[i])) == -1)
			return (i + 1);
		i++;
	}
	if (ft_safe_mutex(INIT, &(data->synch)) == -1)
		return (i + 1);
	i++;
	if (ft_safe_mutex(INIT, &(data->dead_mtx)) == -1)
		return (i + 1);
	i++;
	if (ft_safe_mutex(INIT, &(data->print)) == -1)
		return (i + 1);
	ft_assign_forks(data);
	return(0);
}

//odd or even depends on philo's id
static void ft_assign_forks(t_data *data)
{
	int i;

	i = 0;
	while(i < data->nr_of_philos)
	{
		ft_assign_mtx(&(data->philos[i]), i, data);
		i++;
	}
}

static void ft_assign_mtx(t_philo *philo, int i, t_data *data)
{
	if (data->nr_of_philos == 1)
	{
		philo->l_fork_mtx = &(data->forks[i]);
		philo->r_fork_mtx = &(data->forks[i]);
	}
	else if(i == 0)
	{
		philo->l_fork_mtx = &(data->forks[i]);
		philo->r_fork_mtx = &(data->forks[data->nr_of_philos - 1]);
	}
	else
	{
		philo->l_fork_mtx = &(data->forks[i]);
		philo->r_fork_mtx = &(data->forks[i - 1]);
	}	 
}