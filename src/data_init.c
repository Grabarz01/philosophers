/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrabows <fgrabows@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:15:00 by fgrabows          #+#    #+#             */
/*   Updated: 2024/12/08 20:44:00 by fgrabows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_init_philos(t_data *data);

int	ft_data_init(t_data *data)
{
	data->philos = NULL;
	data->forks = NULL;
	data->dead = false;
	data->error = false;
	data->all_full = 0;
	if (ft_init_philos(data) == -1)
		return (-1);
	data->forks = malloc(sizeof(t_mtx) * data->nr_of_philos);
	if (!data->forks)
	{
		free(data->philos);
		return (ft_error_message(NO_MEM));
	}
	return (0);
}

static int	ft_init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->nr_of_philos);
	if (!data->philos)
		return (ft_error_message(NO_MEM));
	while (i < data->nr_of_philos)
	{
		(data->philos)[i].meals_needed = data->max_meals;
		(data->philos)[i].id = i + 1;
		(data->philos)[i].data = data;
		(data->philos)[i].meal_count = 0;
		ft_safe_mutex(INIT, &(data->philos[i].last_meal_mtx));
		i++;
	}
	return (0);
}
