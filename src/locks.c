/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrabows <fgrabows@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:20:44 by fgrabows          #+#    #+#             */
/*   Updated: 2024/11/17 18:13:36 by fgrabows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_lock_prinft(int value, t_data *data, t_tmv cur_time, int id)
{
	long msec;
	msec = ft_get_msec(data->beginning, cur_time);
	
	ft_safe_mutex(LOCK ,&data->print);
	if(value == EATING)
	{
		printf("%ld ms %d has taken a fork\n", msec, id);
		printf("%ld ms %d has taken a fork\n", msec, id);
		printf("%ld ms %d is eating\n", msec, id);
	}
	else if (value == SLEEPING)
		printf("%ld ms %d is thinking\n", msec, id);
	else if(value == DEAD)
		printf("%ld ms %d died\n", msec, id);
	ft_safe_mutex(UNLOCK ,&data->print);
}

long ft_get_msec(t_tmv start, t_tmv end)
{
	long msec;
	
	msec = ((long)(end.tv_sec - start.tv_sec)) * 1000 +
			((long)(end.tv_usec - start.tv_usec)) / 1000;
	return (msec);	
}
