/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:03:33 by rgallien          #+#    #+#             */
/*   Updated: 2024/06/23 17:57:08 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(char *str)
{
	long	i;
	long	res;

	res = 0;
	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		res = (res * 10) + (str[i] - 48);
		i++;
	}
	if (res > 2147483647)
		return (-1);
	return (res);
}

int	ft_strlen(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		i++;
	return (i);
}

int	is_numbers(char *argv[])
{
	int	i;
	int	j;
	int	bool;

	bool = 0;
	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (argv[i][j] == '+' && bool == 0)
			{
				bool = 1;
				j++;
			}
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (0);
		}
	}
	return (1);
}

int	check_args(char *argv[])
{
	int	i;

	i = 0;
	if (!is_numbers(argv))
		return (0);
	while (argv[++i])
	{
		if (ft_atol(argv[i]) < 1)
			return (0);
	}
	return (1);
}
