/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrabows <fgrabows@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:11:43 by fgrabows          #+#    #+#             */
/*   Updated: 2024/11/18 17:49:38 by fgrabows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//micro 10 -6  mili 10-3
/*allocated
- array of integers 
*/

int main(int argc, char **argv)
{
	t_data data;
	int nr_of_mtxes;
	
	nr_of_mtxes = 0;
	if (ft_input_checker(argc, argv) == -1)
		return (1);
	if (ft_data_init(&data, argc, argv) == -1)
	{
		ft_free_resources(&data);
		return (1);
	}
	ft_init_mutexes(&data);
	if (ft_init_threads(data.nr_of_philos, &data) == -1)
	{
		ft_free_resources(&data);
		return (1);
	}
	ft_wait_threads(&data);
	ft_free_resources(&data);
	return(0);
}


