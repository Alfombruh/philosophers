/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofernan <jofernan@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:45:25 by jofernan          #+#    #+#             */
/*   Updated: 2022/01/14 19:00:12 by jofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define RED     "\033[1;31m"
# define WHITE	"\033[1;37m"
# define RESET   "\033[0;m"
# define BOLDRED     "\033[1;m\033[1;31m"

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

typedef struct s_philo
{
	struct s_info	*info;
	int				n;
	int				lf;
	int				rf;
	int				meals;
	int				time;
	pthread_t		th;
}	t_philo;

typedef struct s_info
{
	t_philo			*philo;
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				meals;
	int				base_t;
	int				stop;
	pthread_mutex_t	dead;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
}	t_info;

int			ft_error(char *msg);
int			ft_time(void);
int			ft_usleep(int ms, t_philo *philo);
int			ft_dead(t_philo *philo);
void		ft_prints(char *msg, t_philo *philo, int i);
int			ft_eating(t_philo *philo);
int			ft_sleeping(t_philo *philo);
int			ft_thinking(t_philo *philo);
int			ft_eaten(t_info *info);
long long	ft_atoi(const char *s);
int			ft_start(t_info *info);

#endif
