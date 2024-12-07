/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrabows <fgrabows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:56:10 by fgrabows          #+#    #+#             */
/*   Updated: 2024/12/07 10:49:46 by fgrabows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_get_diff(t_tmv beginning, t_tmv end)
{
	long	usec;

	usec = ft_get_sec_diff(beginning, end) * 1000000;
	usec += ft_get_usec_diff(beginning, end);
	return (usec);
}

long	ft_get_sec_diff(t_tmv beginning, t_tmv end)
{
	return (end.tv_sec - beginning.tv_sec);
}

long	ft_get_usec_diff(t_tmv beginning, t_tmv end)
{
	return (end.tv_usec - beginning.tv_usec);
}

long	ft_get_msec(t_tmv start, t_tmv end)
{
	long	msec;

	msec = ((long)(end.tv_sec - start.tv_sec)) * 1000
		+ ((long)(end.tv_usec - start.tv_usec)) / 1000;
	return (msec);
}
