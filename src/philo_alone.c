/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_alone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrabows <fgrabows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 10:51:30 by fgrabows          #+#    #+#             */
/*   Updated: 2024/12/07 10:51:32 by fgrabows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_philo_alone(void *arg)
{
	t_philo	*philo;
	t_tmv	time;

	philo = (t_philo *)arg;
	ft_safe_mutex(LOCK, &philo->data->synch);
	ft_safe_mutex(UNLOCK, &philo->data->synch);
	ft_safe_mutex(LOCK, philo->l_fork_mtx);
	ft_print_fork(philo, philo->data, time, philo->id);
	ft_safe_mutex(UNLOCK, philo->l_fork_mtx);
	return (NULL);
}
