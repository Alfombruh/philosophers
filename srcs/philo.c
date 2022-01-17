/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofernan <jofernan@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 19:02:13 by jofernan          #+#    #+#             */
/*   Updated: 2022/01/15 14:24:27 by jofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_error(char *msg)
{
	printf("%serror:%s%s%s%s\n", RED, RESET, WHITE, msg, RESET);
	return (1);
}

static void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	philo->time = ft_time();
	if (philo->n % 2 == 0)
		usleep(10000);
	while (1)
	{
		if (ft_eating(philo))
			break ;
		if (philo->info->meals && ft_eaten(philo->info))
			break ;
		if (ft_sleeping(philo))
			break ;
		if (ft_thinking(philo))
			break ;
	}
	return (NULL);
}

int	ft_start(t_info *info)
{
	int	i;

	i = -1;
	info->base_t = ft_time();
	while (++i < info->n_philo)
		if (pthread_create(&info->philo[i].th, NULL,
				ft_routine, &info->philo[i]))
			return (ft_error("couldn't join philo.th"));
	i = -1;
	while (++i < info->n_philo)
		if (pthread_join(info->philo[i].th, NULL))
			return (ft_error("couldn't join philo.th"));
	return (0);
}
