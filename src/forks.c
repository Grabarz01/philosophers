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

void ft_init_mutexes(t_data *data)
{
	int i;
	
	i = 0;
	while (i < data->nr_of_philos)
	{
		ft_safe_mutex(INIT, &(data->forks[i]));
		i++;
	}
	ft_safe_mutex(INIT, &(data->synch));
	ft_safe_mutex(INIT, &(data->dead_mtx));
	ft_safe_mutex(INIT, &(data->print));
	ft_safe_mutex(INIT, &(data->full_mtx));
	ft_assign_forks(data);
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