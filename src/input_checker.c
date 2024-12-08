/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrabows <fgrabows@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:40:19 by fgrabows          #+#    #+#             */
/*   Updated: 2024/12/08 20:31:54 by fgrabows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
Format I accept is:
- at least 4 up to 5 args(for argc +1)
- only digits
*/
static int	ft_check_arguments(char **argv);
static int	ft_pos_atoi(const char *nptr);
static int	ft_get_values(int argc, char **argv, int **values);

int	ft_input_manager(int argc, char **argv, t_data *data)
{
	int	*values;

	if (!argv)
		return (ft_error_message(NO_ARGS));
	if (argc < 5 || argc > 6)
		return (ft_error_message(WRONG_NR_ARG));
	if (ft_check_arguments(argv) == -1)
		return (-1);
	if (ft_get_values(argc, argv, &values) == -1)
		return (-1);
	data->nr_of_philos = values[0];
	data->lifetime = values[1];
	data->t_eat = values[2];
	data->t_sleep = values[3];
	if (argc == 6)
		data->max_meals = values[4];
	free(values);
	if (data->nr_of_philos == 0)
		return (ft_error_message(NO_PHILO));
	return (0);
}

static int	ft_check_arguments(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		if (!argv[i][j])
			return (ft_error_message(EMPTY_ARG));
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (ft_error_message(WRONG_TYP_ARG));
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	ft_get_values(int argc, char **argv, int **values)
{
	int	i;
	int	*new_values;

	new_values = malloc(sizeof(int) * (argc - 1));
	if (!new_values)
		return (ft_error_message(NO_MEM));
	i = 0;
	while (argv[i + 1])
	{
		new_values[i] = ft_pos_atoi(argv[i + 1]);
		if (new_values[i] == -1)
		{
			free(new_values);
			return (-1);
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
