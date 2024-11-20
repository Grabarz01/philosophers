/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_pthreads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrabows <fgrabows@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:58:50 by fgrabows          #+#    #+#             */
/*   Updated: 2024/11/16 16:51:08 by fgrabows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_safe_pthread(pthread_t *thread, t_optype type, t_philo *philo, t_data *data)
{
	int value;

	value = 0;
	if (type == CREATE_MONITOR)
		value = pthread_create(thread, NULL, &ft_monitor, data);
	else if (type == CREATE_PHILO)
		value = pthread_create(thread, NULL, &ft_philo, philo);
	else if (type == JOIN)
		value = pthread_join(*thread, NULL);
	if (value != 0)
		return (ft_error_message(PTHR_ERR));
	return (0);
}
