/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrabows <fgrabows@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:39:27 by fgrabows          #+#    #+#             */
/*   Updated: 2024/11/18 18:05:13 by fgrabows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int ft_destroy_mutexes(t_data *data, int nr);

int ft_free_resources(t_data *data, bool mutex, int nr)
{
	int error;
	int i;

	i = 0;
	error = 0;
	if (mutex == true && ft_destroy_mutexes(data, nr) == -1)
		error = -1;
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
	return(error);
}

static int ft_destroy_mutexes(t_data *data, int nr)
{
	int i;
	int error;
	
	error = 0;
	i = 0;
	while(i <= nr - data->nr_of_philos)
	{
		if(ft_safe_mutex(DESTROY, &(data->philos[i].last_meal_mtx)) == -1)
			error = -1;
		if(ft_safe_mutex(DESTROY, &(data->forks[i])) == -1)
			error = -1;
		i++;
	}
	if (nr >= data->nr_of_philos + 1)
		ft_safe_mutex(DESTROY, &(data->synch));
	if (nr >= data->nr_of_philos + 2)
		ft_safe_mutex(DESTROY, &(data->dead_mtx));
	if (nr >= data->nr_of_philos + 3)
		ft_safe_mutex(DESTROY, &(data->print));
	//to change
	if (error != 0)
		return (ft_error_message("Error ocured while destroying mutexes\n"));
	return(0);
}
int ft_i_threads_destroy(t_data *data, int i)
{
	int j;

	data->error = true;
	ft_safe_mutex(UNLOCK, &(data->synch));
	j = 0;
	while (j < i)
	{
		pthread_join(data->philos[j].philo, NULL);
		i++;
	}
	return(ft_error_message(THRED_ERR));
}

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