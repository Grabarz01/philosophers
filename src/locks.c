/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrabows <fgrabows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:20:44 by fgrabows          #+#    #+#             */
/*   Updated: 2024/12/07 09:35:33 by fgrabows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_print_eat(t_philo *philo, t_data *data, t_tmv cur_time, int id)
{
	long msec;
	
	if (ft_am_i_dead(philo) == 1)
		return (1);
	ft_safe_mutex(LOCK ,&data->print);
	gettimeofday(&cur_time, NULL);
	msec = ft_get_msec(data->beginning, cur_time);
	printf("%ld ms %d has taken a fork\n", msec, id);
	printf("%ld ms %d is eating\n", msec, id);
	ft_safe_mutex(UNLOCK ,&data->print);
	return(0);
}

int ft_print_fork(t_philo *philo, t_data *data, t_tmv cur_time, int id)
{
	long msec;
	
	if (ft_am_i_dead(philo) == 1)
		return (1);
	ft_safe_mutex(LOCK ,&data->print);
	gettimeofday(&cur_time, NULL);
	msec = ft_get_msec(data->beginning, cur_time);
	printf("%ld ms %d has taken a fork\n", msec, id);
	ft_safe_mutex(UNLOCK ,&data->print);
	return (0);
}

int ft_print_sleep(t_philo *philo, t_data *data, t_tmv cur_time, int id)
{
	long msec;
	
	if (ft_am_i_dead(philo) == 1)
		return (1);
	ft_safe_mutex(LOCK ,&data->print);
	gettimeofday(&cur_time, NULL);
	msec = ft_get_msec(data->beginning, cur_time);
	printf("%ld ms %d is sleeping\n", msec, id);
	ft_safe_mutex(UNLOCK ,&data->print);
	return (0);
}

int ft_print_died(t_philo *philo, t_data *data, t_tmv cur_time, int id)
{
	long msec;
	ft_safe_mutex(LOCK ,&data->print);
	gettimeofday(&cur_time, NULL);
	msec = ft_get_msec(data->beginning, cur_time);
	printf("%ld ms %d died\n", msec, id);
	ft_safe_mutex(UNLOCK ,&data->print);
	return (0);
}
int ft_print_think(t_philo *philo, t_data *data, t_tmv cur_time, int id)
{
	long msec;
	
	if (ft_am_i_dead(philo) == 1)
		return (1);
	ft_safe_mutex(LOCK ,&data->print);
	gettimeofday(&cur_time, NULL);
	msec = ft_get_msec(data->beginning, cur_time);
	printf("%ld ms %d is thinking\n", msec, id);	
	ft_safe_mutex(UNLOCK ,&data->print);
	return (0);
}
