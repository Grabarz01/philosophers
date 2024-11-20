/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrabows <fgrabows@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:40:19 by fgrabows          #+#    #+#             */
/*   Updated: 2024/11/16 16:12:20 by fgrabows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
Format I accept is:
- at least 4 up to 5 args(for argc +1)
- only digits
*/
static int ft_check_arguments(char **argv);


int ft_input_checker(int argc, char **argv)
{
	if (!argv)
		return(ft_error_message(NO_ARGS));
	if (argc < 5 || argc > 6)
		return(ft_error_message(WRONG_NR_ARG));
	if (ft_check_arguments(argv) == -1)
		return (-1);
	return(0);
}

static int ft_check_arguments(char **argv)
{
	int i;
	int j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		if(!argv[i][j])
			return (ft_error_message(EMPTY_ARG));
		while(argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (ft_error_message(WRONG_TYP_ARG));
			j++;
		}
		j = 0;		
		i++;
	}
	return(0);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}