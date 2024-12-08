/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrabows <fgrabows@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:11:43 by fgrabows          #+#    #+#             */
/*   Updated: 2024/12/08 19:42:55 by fgrabows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		nr_of_mtxes;

	nr_of_mtxes = 0;
	if (ft_input_manager(argc, argv, &data) == -1)
		return (1);
	if (ft_data_init(&data) == -1)
		return (1);
	ft_init_mutexes(&data);
	ft_init_threads(data.nr_of_philos, &data);
	ft_wait_threads(&data);
	ft_free_resources(&data);
	return (0);
}
