/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrabows <fgrabows@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:56:51 by fgrabows          #+#    #+#             */
/*   Updated: 2024/11/22 16:27:58 by fgrabows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_safe_mutex(t_optype type, t_mtx *mutex)
{
	int value;

	value = 0;
	if (type == LOCK)
		value = pthread_mutex_lock(mutex);
	else if (type == UNLOCK)
		value = pthread_mutex_unlock(mutex);
	else if (type == INIT)
		value = pthread_mutex_init(mutex, NULL);
	else if (type == DESTROY)
		value = pthread_mutex_destroy(mutex);
	if (value != 0)
	{
		printf("Mutex operation failed (error code %d)\n", value);
		perror(NULL);
		return(-1);
	}
	return (0);
}
