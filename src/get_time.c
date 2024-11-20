/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrabows <fgrabows@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:56:10 by fgrabows          #+#    #+#             */
/*   Updated: 2024/11/15 15:19:10 by fgrabows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long ft_get_diff(t_tmv beginning , t_tmv end)
{
	long usec;
	
	usec = ft_get_sec_diff(beginning, end) * 1000000;
	usec += ft_get_usec_diff(beginning, end);
	return (usec);
}

long ft_get_sec_diff(t_tmv beginning , t_tmv end)
{
	return (end.tv_sec - beginning.tv_sec);
}
long ft_get_usec_diff(t_tmv beginning , t_tmv end)
{
	return (end.tv_usec - beginning.tv_usec);
}