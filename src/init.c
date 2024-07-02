/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:58:45 by rgallien          #+#    #+#             */
/*   Updated: 2024/07/02 15:57:43 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_forks(t_prog *prog, pthread_mutex_t *forks, long nb_philo)
{
	long	i;

	pthread_mutex_init(&prog->m_dead, NULL);
	pthread_mutex_init(&prog->m_print, NULL);
	i = 0;
	while (i < nb_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < nb_philo)
	{
		prog->ph[i].m_dead = &prog->m_dead;
		prog->ph[i].m_print = &prog->m_print;
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
	prog->ph = malloc(sizeof(t_philo) * ft_atol(argv[0]));
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
		prog->ph[i].is_dead = 0;
		prog->ph[i].nb_eat = 0;
		if (argv[4])
			prog->ph[i].must_eat = ft_atol(argv[4]);
		else
			prog->ph[i].must_eat = -1;
		i++;
	}
}

void	ft_init(t_prog *prog, char *argv[], pthread_mutex_t *forks)
{
	init_philos(prog, argv);
	init_forks(prog, forks, ft_atol(argv[0]));
}
