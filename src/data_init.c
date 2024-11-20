/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrabows <fgrabows@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:15:00 by fgrabows          #+#    #+#             */
/*   Updated: 2024/11/18 17:54:01 by fgrabows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_pos_atoi(const char *nptr);
static void ft_set_input_values(int *values, t_data *data, int argc);
static int ft_init_philos(t_data *data);
static int ft_get_values(int argc, char **argv, int **values);

int ft_data_init(t_data *data, int argc, char **argv)
{
	int *values;
	
	data->philos = NULL;
	data->forks = NULL;
	data->dead = false;
	data->error = false;
	if (ft_get_values(argc, argv, &values) == -1)
		return (-1);
	ft_set_input_values(values, data, argc);
	if (data->nr_of_philos == 0)
		return (ft_error_message(NO_PHILO));
	if (ft_init_philos(data) == -1)
		return(-1);
	data->forks = malloc(sizeof(t_mtx) * data->nr_of_philos);
	if (!data->forks)
		return(ft_error_message(NO_MEM));
	return(0);
}

static int ft_init_philos(t_data *data)
{
	int i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->nr_of_philos);
	if (!data->philos)
		return(ft_error_message(NO_MEM));
	while(i < data->nr_of_philos)
	{
		(data->philos)[i].id = i + 1;
		(data->philos)[i].data = data;
		ft_safe_mutex(INIT, &(data->philos[i].last_meal_mtx));
		i++;
	}
	return (0);
}
static void ft_set_input_values(int *values, t_data *data, int argc)
{
	data->nr_of_philos = values[0];
	data->lifetime = values[1];
	data->t_eat = values[2];
	data->t_sleep = values[3];
	if (argc == 6)
		data->max_meals = values[4];
	free(values);
}
static int ft_get_values(int argc, char **argv, int **values)
{
	int i;
	int *new_values;
	
	new_values = malloc(sizeof(int) * (argc - 1));
	if(!new_values)
		return(ft_error_message(NO_MEM));
	i = 0;
	while (argv[i + 1])
	{
		new_values[i] = ft_pos_atoi(argv[i + 1]);
		if (new_values[i] == -1)
		{
			free(new_values);
			return(-1);
		}
		i++;
	}
	*values = new_values;
	return (0);
}

static int	ft_pos_atoi(const char *nptr)
{
	int		i;
	long	nb;

	i = 0;
	nb = 0;
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + (nptr[i] - '0');
		i++;
		if (nb > INT_MAX)
		{
			printf("%s\n", TOO_BIG);
			return (-1);
		}
	}
	return ((int)nb);
}