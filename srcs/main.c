/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofernan <jofernan@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 19:02:05 by jofernan          #+#    #+#             */
/*   Updated: 2022/01/15 14:08:48 by jofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_free(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->n_philo)
	{
		if (pthread_mutex_unlock(&info->forks[i]))
			return (ft_error("couldn't unlock forks mutex"));
		if (pthread_mutex_destroy(&info->forks[i]))
			return (ft_error("couldn't destoy forks mutex"));
	}
	if (pthread_mutex_destroy(&info->print)
		|| pthread_mutex_destroy(&info->dead))
		return (ft_error("coudln't destroy print or dead mutex"));
	free(info->philo);
	free(info->forks);
	return (0);
}

static int	ft_philos(t_info *info)
{
	int	i;

	i = -1;
	info->philo = (t_philo *)malloc(sizeof(t_philo) * info->n_philo);
	if (!info->philo)
		return (ft_error("couldn't allocate memory for the philos"));
	while (++i < info->n_philo)
	{
		info->philo[i].info = info;
		info->philo[i].n = i + 1;
		info->philo[i].lf = i;
		info->philo[i].rf = (i + 1) % info->n_philo;
		info->philo[i].meals = 0;
	}
	return (0);
}

static int	ft_forks(t_info *info)
{
	int	i;

	i = -1;
	info->forks = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * info->n_philo);
	if (!info->forks)
		return (ft_error("couldn't allocate memory for the forks array"));
	while (++i < info->n_philo)
		if (pthread_mutex_init(&info->forks[i], NULL))
			return (ft_error("forks mutex_init failed"));
	if (pthread_mutex_init(&info->print, NULL)
		|| pthread_mutex_init(&info->dead, NULL))
		return (ft_error("print or dead mutex couldn't initialize"));
	return (0);
}

static int	ft_init(t_info *info, char **argv, int argc)
{
	info->n_philo = ft_atoi(argv[1]);
	info->t_die = ft_atoi(argv[2]);
	info->t_eat = ft_atoi(argv[3]);
	info->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->meals = ft_atoi(argv[5]);
	if (ft_forks(info))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc < 5 || argc > 6)
		return (ft_error("./philo n_philo t_dead t_eat t_sleep (meals)"));
	memset(&info, 0, sizeof(info));
	if (ft_init(&info, argv, argc))
		return (1);
	if (ft_philos(&info))
		return (1);
	if (ft_start(&info))
		return (1);
	if (ft_free(&info))
		return (1);
}
