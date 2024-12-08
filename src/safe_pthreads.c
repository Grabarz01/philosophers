/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_pthreads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrabows <fgrabows@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:58:50 by fgrabows          #+#    #+#             */
/*   Updated: 2024/12/08 20:41:37 by fgrabows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_threads(int nr_of_philos, t_data *data)
{
	int	i;

	i = -1;
	ft_safe_mutex(LOCK, &data->synch);
	while (++i < nr_of_philos)
	{
		if (nr_of_philos == 1)
			ft_safe_pthread(&(data->philos[i].philo),
				CREATE_ALONE, &(data->philos[i]), NULL);
		else
			ft_safe_pthread(&(data->philos[i].philo),
				CREATE_PHILO, &(data->philos[i]), NULL);
	}
	ft_safe_pthread(&data->monitor, CREATE_MONITOR, NULL, data);
	i = 0;
	gettimeofday(&data->beginning, NULL);
	while (i < nr_of_philos)
	{
		ft_safe_mutex(LOCK, &(data->philos[i].last_meal_mtx));
		data->philos[i].last_meal.tv_sec = data->beginning.tv_sec;
		data->philos[i].last_meal.tv_usec = data->beginning.tv_usec;
		ft_safe_mutex(UNLOCK, &(data->philos[i].last_meal_mtx));
		i++;
	}
	ft_safe_mutex(UNLOCK, &data->synch);
}

int	ft_safe_pthread(pthread_t *thread, t_optype type,
	t_philo *philo, t_data *data)
{
	int	value;

	value = 0;
	if (type == CREATE_MONITOR)
		value = pthread_create(thread, NULL, &ft_monitor, data);
	else if (type == CREATE_PHILO)
		value = pthread_create(thread, NULL, &ft_philo, philo);
	else if (type == CREATE_ALONE)
		value = pthread_create(thread, NULL, &ft_philo_alone, philo);
	else if (type == JOIN)
		value = pthread_join(*thread, NULL);
	if (value != 0)
		return (ft_error_message(PTHR_ERR));
	return (0);
}
