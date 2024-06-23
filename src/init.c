/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:58:45 by rgallien          #+#    #+#             */
/*   Updated: 2024/06/23 19:11:32 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_forks(t_prog *prog, pthread_mutex_t *forks)
{
	size_t	i;

	i = 0;
	while (i < prog->ph[i].nb_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < prog->ph[i].nb_philos)
	{
		prog->ph[i].l_fork = &forks[i];
		if (prog->ph[i].id == 1)
			prog->ph[i].r_fork = &forks[prog->ph[i].nb_philos - 1];
		else
			prog->ph[i].r_fork = &forks[i - 1];
		i++;
	}
}

void	init_philos(t_prog *prog, char *argv[])
{
	size_t	i;

	i = 0;
	prog->ph = malloc(sizeof(t_philo) * ft_atol(argv[1]));
	if (!prog->ph)
		perror("init of prog->ph failed\n");
	while (i < (long unsigned int)ft_atol(argv[0]))
	{
		prog->ph[i].id = i + 1;
		prog->ph[i].last_meal = get_current_time();
		prog->ph[i].nb_philos = ft_atol(argv[0]);
		prog->ph[i].start = get_current_time();
		prog->ph[i].time_die = ft_atol(argv[1]);
		prog->ph[i].time_eat = ft_atol(argv[2]);
		prog->ph[i].time_sleep = ft_atol(argv[3]);
		if (argv[4])
			prog->ph[i].must_eat = ft_atol(argv[4]);
		else
			prog->ph[i].must_eat = -1;
		i++;
	}
}

void	ft_init(t_prog *prog, char *argv[])
{
	pthread_mutex_t	*forks;

	forks = malloc(sizeof(pthread_mutex_t) * ft_atol(argv[0]));
	if (!forks)
		perror("init of forks failed\n");
	init_philos(prog, argv);
	init_forks(prog, forks);
}
