/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrabows <fgrabows@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:16:17 by fgrabows          #+#    #+#             */
/*   Updated: 2024/11/18 14:29:28 by fgrabows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
//more precise usleep function 
void ft_my_usleep(long usec,  t_tmv t_start)
{
	t_tmv	t_cur;
	long	diff;
	long	rem;

	if (usec < 0)
		return ;
	diff = 0;
	while (diff < usec)
	{
		rem = usec - diff;
		if(rem > 1000)
			usleep(rem - 1000);
		gettimeofday(&t_cur, NULL);	
		diff = (long)((t_cur.tv_sec - t_start.tv_sec) * 1000000 + (t_cur.tv_usec - t_start.tv_usec));
	}
}