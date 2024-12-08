/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrabows <fgrabows@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:29:56 by fgrabows          #+#    #+#             */
/*   Updated: 2024/12/08 20:30:49 by fgrabows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	*ft_monitor(void *arg)
{
	t_data	*data;
	int		status;
	int		i;

	data = (t_data *)arg;
	ft_safe_mutex(LOCK, &data->synch);
	ft_safe_mutex(UNLOCK, &data->synch);
	i = 0;
	while (1)
	{
		while (i < data->nr_of_philos)
		{
			if (ft_are_u_ok(&(data->philos[i])) == 1)
				return (NULL);
			i++;
		}
		usleep(1000);
		i = 0;
	}
	return (NULL);
}

int	ft_are_u_ok(t_philo *philo)
{
	t_tmv	cur;

	ft_safe_mutex(LOCK, &(philo->last_meal_mtx));
	gettimeofday(&cur, NULL);
	if (ft_get_msec(philo->last_meal, cur) > philo->data->lifetime)
	{
		ft_safe_mutex(UNLOCK, &(philo->last_meal_mtx));
		ft_safe_mutex(LOCK, &(philo->data->dead_mtx));
		if (philo->data->dead == true)
		{
			ft_safe_mutex(UNLOCK, &(philo->data->dead_mtx));
			return (1);
		}
		philo->data->dead = true;
		ft_safe_mutex(UNLOCK, &(philo->data->dead_mtx));
		ft_print_died(philo, philo->data, cur, philo->id);
		return (1);
	}
	ft_safe_mutex(UNLOCK, &(philo->last_meal_mtx));
	ft_safe_mutex(LOCK, &(philo->data->full_mtx));
	if (philo->data->all_full == philo->data->max_meals)
	{
		ft_safe_mutex(UNLOCK, &(philo->data->full_mtx));
		return (1);
	}
	ft_safe_mutex(UNLOCK, &(philo->data->full_mtx));
	return (0);
}

int	ft_am_full(t_philo *philo)
{
	ft_safe_mutex(LOCK, &(philo->data->full_mtx));
	philo->data->all_full++;
	if (philo->data->all_full == philo->data->nr_of_philos)
	{
		ft_safe_mutex(LOCK, &philo->data->dead_mtx);
		philo->data->dead = true;
		ft_safe_mutex(UNLOCK, &philo->data->dead_mtx);
		ft_safe_mutex(UNLOCK, &(philo->data->full_mtx));
		return (1);
	}
	ft_safe_mutex(UNLOCK, &(philo->data->full_mtx));
	return (0);
}
