/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrabows <fgrabows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:39:27 by fgrabows          #+#    #+#             */
/*   Updated: 2024/12/07 09:46:03 by fgrabows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void ft_destroy_mutexes(t_data *data);

int ft_free_resources(t_data *data)
{
	int error;
	int i;

	i = 0;
	error = 0;
	ft_destroy_mutexes(data);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
	return(error);
}

static void ft_destroy_mutexes(t_data *data)
{
	int i;

	i = 0;
	while(i < data->nr_of_philos)
	{
		ft_safe_mutex(DESTROY, &(data->philos[i].last_meal_mtx));
		ft_safe_mutex(DESTROY, &(data->forks[i]));
		i++;
	}
	ft_safe_mutex(DESTROY, &(data->synch));
	ft_safe_mutex(DESTROY, &(data->dead_mtx));
	ft_safe_mutex(DESTROY, &(data->print));
}
// int ft_i_threads_destroy(t_data *data, int i)
// {
// 	int j;

// 	data->error = true;
// 	ft_safe_mutex(UNLOCK, &(data->synch));
// 	j = 0;
// 	while (j < i)
// 	{
// 		pthread_join(data->philos[j].philo, NULL);
// 		i++;
// 	}
// 	return(ft_error_message(THRED_ERR));
// }

void ft_wait_threads(t_data *data)
{
	int i;

	i = 0;
	while(i < data->nr_of_philos)
	{
		ft_safe_pthread(&(data->philos[i].philo), JOIN, NULL, NULL);
		i++;
	}
	ft_safe_pthread(&(data->monitor), JOIN, NULL, NULL);
}