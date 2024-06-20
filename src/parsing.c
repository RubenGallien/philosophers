/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:17:36 by rgallien          #+#    #+#             */
/*   Updated: 2024/06/20 17:58:47 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_numbers(char **argv)
{
	int	i;
	int	j;
	int	bool;

	i = 1;
	bool = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][0] == '+' && bool == 0)
			{
				j++;
				bool = 1;
			}
			if (ft_strlen(argv[i]) > 11)
				return (0);
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_args(char **argv, t_program *philos)
{
	int	i;
	if (!is_numbers(argv))
		return (0);
	philos->ph = (t_philo *)malloc(sizeof(t_philo) * ft_atol(argv[1]));
	if (!philos)
		return (0);
	i = -1;
	while (++i < ft_atol(argv[1]))
	{
		philos->ph[i].num_of_philos = ft_atol(argv[1]);
		philos->ph[i].time_to_die = ft_atol(argv[2]);
		philos->ph[i].time_to_eat = ft_atol(argv[3]);
		philos->ph[i].time_to_sleep = ft_atol(argv[4]);
		if (philos->ph[i].num_of_philos < 1 || philos->ph[i].time_to_die < 1 \
		|| philos->ph[i].time_to_eat < 1 || philos->ph[i].time_to_sleep < 1)
			return (ft_free_philos(philos, i), 0);
		if (argv[5])
			philos->ph[i].num_times_to_eat = ft_atol(argv[5]);
		else
			philos->ph[i].num_times_to_eat = 0;
		philos->ph[i].meals_eaten = 0;
		philos->ph[i].id = i + 1;
	}
	// i = 0;
	// while (i  < ft_atol(argv[1]))
	// {
	// 	printf("philos->ph[i]: %p\n", (void*)&philos->ph[i]);
    //     printf("philos->mutex: %p\n", (void*)&philos->mutex);
    //     printf("philos->ph[i].id: %d\n", philos->ph[i].id);
    //     printf("philos->ph[i].num_of_philos: %d\n", philos->ph[i].num_of_philos);
    //     printf("philos->ph[i].time_to_die: %zu\n", philos->ph[i].time_to_die);
    //     printf("philos->ph[i].time_to_eat: %zu\n", philos->ph[i].time_to_eat);
    //     printf("philos->ph[i].time_to_sleep: %zu\n", philos->ph[i].time_to_sleep);
	// 	i++;
	// }
	return (1);
}
