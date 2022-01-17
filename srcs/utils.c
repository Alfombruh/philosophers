/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofernan <jofernan@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 19:02:21 by jofernan          #+#    #+#             */
/*   Updated: 2022/01/15 14:08:47 by jofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

int	ft_dead(t_philo *philo)
{
	if (philo->info->stop)
	{
		pthread_mutex_unlock(&philo->info->forks[philo->lf]);
		pthread_mutex_unlock(&philo->info->forks[philo->rf]);
		return (1);
	}
	if (ft_time() - philo->time > philo->info->t_die)
	{
		pthread_mutex_lock(&philo->info->dead);
		philo->info->stop = 1;
		pthread_mutex_unlock(&philo->info->dead);
		printf("%d\t %d died\n", ft_time() - philo->info->base_t, philo->n);
		pthread_mutex_unlock(&philo->info->forks[philo->lf]);
		pthread_mutex_unlock(&philo->info->forks[philo->rf]);
		return (1);
	}
	return (0);
}

static int	time_diff(struct timeval t1)
{
	struct timeval	t2;

	gettimeofday(&t2, NULL);
	return ((t2.tv_sec * 1000 + t2.tv_usec / 1000)
		- (t1.tv_sec * 1000 + t1.tv_usec / 1000));
}

void	ft_prints(char *msg, t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->info->print);
	if (i && !philo->info->stop)
	{
		if (!philo->info->meals || msg[3] != 'e' )
			printf("%d\t %d %s\n", ft_time() - philo->info->base_t,
				philo->n, msg);
		else if (philo->info->meals && msg[3] == 'e')
			printf("%d\t %d %s [%d]\n", ft_time() - philo->info->base_t,
				philo->n, msg, ++philo->meals);
	}
	else if (!philo->info->stop)
		printf("%d\t %d \033[1;34m%s\033[0;m\n",
			ft_time() - philo->info->base_t, philo->n, msg);
	pthread_mutex_unlock(&philo->info->print);
}

int	ft_usleep(int ms, t_philo *philo)
{
	struct timeval	t1;

	gettimeofday(&t1, NULL);
	while (ms > time_diff(t1))
	{
		usleep(100);
		if (ft_dead(philo))
			return (1);
	}
	return (0);
}
