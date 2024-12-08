/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrabows <fgrabows@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:44:53 by fgrabows          #+#    #+#             */
/*   Updated: 2024/12/08 20:41:20 by fgrabows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_odd_philo(t_philo *philo, int id);
static int	ft_even_philo(t_philo *philo, int id);
static int	ft_forks_taken(t_philo *philo, t_tmv *tmp);

int	ft_get_forks(t_philo *philo)
{
	if (ft_am_i_dead(philo) == 1)
		return (1);
	if (philo->id % 2 == 0)
	{
		if (ft_even_philo(philo, philo->id) == 1)
			return (1);
	}
	else
	{
		if (ft_odd_philo(philo, philo->id) == 1)
			return (1);
	}
	if (ft_am_i_dead(philo) == 1)
		return (1);
	ft_after_sleep(philo, philo->data);
	return (0);
}

static int	ft_odd_philo(t_philo *philo, int id)
{
	t_tmv	tmp;

	ft_safe_mutex(LOCK, philo->l_fork_mtx);
	if (ft_print_fork(philo, philo->data, tmp, philo->id) == 1)
	{
		ft_safe_mutex(UNLOCK, philo->l_fork_mtx);
		return (1);
	}
	ft_safe_mutex(LOCK, philo->r_fork_mtx);
	if (ft_forks_taken(philo, &tmp) == 1)
		return (1);
	usleep(philo->data->t_eat * 1000);
	ft_safe_mutex(UNLOCK, philo->l_fork_mtx);
	ft_safe_mutex(UNLOCK, philo->r_fork_mtx);
	if (++(philo->meal_count) == philo->meals_needed)
	{
		if (ft_am_full(philo) == 1)
			return (1);
	}
	if (ft_print_sleep(philo, philo->data, tmp, philo->id) == 1)
		return (1);
	if (ft_sleep(philo, tmp) == 1)
		return (1);
	return (0);
}

static int	ft_even_philo(t_philo *philo, int id)
{
	t_tmv	tmp;

	ft_safe_mutex(LOCK, philo->r_fork_mtx);
	if (ft_print_fork(philo, philo->data, tmp, philo->id) == 1)
	{
		ft_safe_mutex(UNLOCK, philo->r_fork_mtx);
		return (1);
	}
	ft_safe_mutex(LOCK, philo->l_fork_mtx);
	if (ft_forks_taken(philo, &tmp) == 1)
		return (1);
	usleep(philo->data->t_eat * 1000);
	ft_safe_mutex(UNLOCK, philo->r_fork_mtx);
	ft_safe_mutex(UNLOCK, philo->l_fork_mtx);
	if (++(philo->meal_count) == philo->meals_needed)
	{
		if (ft_am_full(philo) == 1)
			return (1);
	}
	if (ft_print_sleep(philo, philo->data, tmp, philo->id) == 1)
		return (1);
	if (ft_sleep(philo, tmp) == 1)
		return (1);
	return (0);
}

static int	ft_forks_taken(t_philo *philo, t_tmv *tmp)
{
	ft_safe_mutex(LOCK, &philo->last_meal_mtx);
	gettimeofday(&philo->last_meal, NULL);
	ft_safe_mutex(UNLOCK, &philo->last_meal_mtx);
	if (ft_print_eat(philo, philo->data, *tmp, philo->id) == 1)
	{
		ft_safe_mutex(UNLOCK, philo->r_fork_mtx);
		ft_safe_mutex(UNLOCK, philo->l_fork_mtx);
		return (1);
	}
	return (0);
}
