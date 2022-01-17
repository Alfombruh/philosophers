/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofernan <jofernan@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 19:02:17 by jofernan          #+#    #+#             */
/*   Updated: 2022/01/15 14:08:47 by jofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_thinking(t_philo *philo)
{
	ft_prints("is thinking", philo, 1);
	return (0);
}

int	ft_sleeping(t_philo *philo)
{
	ft_prints("is sleeping", philo, 1);
	if (ft_usleep(philo->info->t_sleep, philo))
		return (1);
	return (0);
}

static int	ft_onephilo(t_philo *philo)
{
	if (ft_dead(philo))
		return (1);
	pthread_mutex_lock(&philo->info->forks[philo->lf]);
	ft_prints("has taken a fork", philo, 0);
	pthread_mutex_unlock(&philo->info->forks[philo->lf]);
	if (ft_dead(philo))
		return (1);
	return (0);
}

int	ft_eating(t_philo *philo)
{
	if (philo->info->n_philo == 1)
		return (ft_onephilo(philo));
	if (ft_dead(philo))
		return (1);
	pthread_mutex_lock(&philo->info->forks[philo->lf]);
	if (ft_dead(philo))
		return (1);
	ft_prints("has taken a fork", philo, 0);
	pthread_mutex_lock(&philo->info->forks[philo->rf]);
	ft_prints("has taken a fork", philo, 0);
	if (ft_dead(philo))
		return (1);
	ft_prints("is eating", philo, 1);
	if (ft_usleep(philo->info->t_eat, philo))
		return (1);
	philo->time = ft_time();
	if (ft_dead(philo))
		return (1);
	pthread_mutex_unlock(&philo->info->forks[philo->lf]);
	pthread_mutex_unlock(&philo->info->forks[philo->rf]);
	if (ft_dead(philo))
		return (1);
	return (0);
}

int	ft_eaten(t_info *info)
{
	int	i;
	int	eaten;

	eaten = 0;
	i = -1;
	while (++i < info->n_philo)
	{
		if (info->philo[i].meals >= info->meals)
			eaten++;
	}
	if (eaten == info->n_philo)
		return (1);
	return (0);
}
