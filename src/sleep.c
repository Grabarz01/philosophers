/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrabows <fgrabows@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 20:26:58 by fgrabows          #+#    #+#             */
/*   Updated: 2024/12/08 20:27:37 by fgrabows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_sleep(t_philo *philo, t_tmv begining)
{
	t_tmv	timer;

	usleep(philo->data->t_sleep * 1000);
	if (ft_print_think(philo, philo->data, timer, philo->id) == 1)
		return (1);
	return (0);
}

static void	ft_after_sleep(t_philo *philo, t_data *data)
{
	int		philo_nr;
	long	time_to_think;

	philo_nr = philo->data->nr_of_philos;
	if (philo_nr % 2 == 0)
		usleep(2000);
	else
	{
		time_to_think = data->t_eat * 2 - data->t_sleep * 2;
		if (time_to_think > 0)
			usleep(time_to_think * 1000);
		else
			usleep(1000);
	}
}

//t_eat t_sleep
// I eating II waiting III waiting
// I thinking/sleeping II eating III waiting
// I has to be thinking until III gets forks II eating/sleeping II eating

//eating+sleeping+thinking > eating + eating + 1