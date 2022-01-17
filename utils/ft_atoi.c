/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofernan <jofernan@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:44:51 by jofernan          #+#    #+#             */
/*   Updated: 2022/01/14 19:02:27 by jofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long long	ft_atoi(const char *s)
{
	long long	num;
	long long	sign;

	while ((*s >= 9 && *s <= 13) || *s == 32)
		s++;
	sign = 1;
	if (*s == '+')
		s++;
	else if (*s == '-')
	{
		sign *= -1;
		s++;
	}
	num = 0;
	while (*s - '0' >= 0 && *s - '0' <= 9)
	{
		num *= 10;
		num += *s - '0';
		s++;
	}
	return (num * sign);
}
