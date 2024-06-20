/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:35:25 by rgallien          #+#    #+#             */
/*   Updated: 2024/06/20 13:18:24 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

long ft_atol(char *str)
{
	long	i;
	long	res;

	i = 0;
	res = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		res = (res * 10) + str[i] - 48;
		i++;
	}
	if (res > 2147483647)
		return (0);
	return (res);
}

void ft_free_philos(t_program *philos, int i)
{
	while(i >= 0)
	{
		free(&philos->ph[i]);
		i--;
	}
}
