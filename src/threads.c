/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:07:38 by rgallien          #+#    #+#             */
/*   Updated: 2024/07/03 17:59:54 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_solo(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	ft_print(philo, "fork");
	ft_usleep(philo->time_die, philo);
	return (NULL);
}

void	*monitoring(void *args)
{
	t_philo	*philos;
	philos = (t_philo *)args;
	while (1)
	{
		if (meal_too_late(philos) || eat_enough(philos))
			break ;
	}
	return (NULL);
}

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->nb_philos % 2 == 0)
		ft_usleep(philo->time_eat * (philo->id % 2), philo);
	else if (philo->nb_philos % 2 == 1)
		ft_usleep(philo->time_eat * (philo->id % 3), philo);
	// if (philo->id % 2 == 0)
	// 	ft_usleep(philo->time_eat, philo);
	while (!ft_is_dead(philo))
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}

void	make_threads(t_prog *prog, long nb_philo, pthread_mutex_t *forks)
{
	long		i;
	pthread_t	monitor;

	i = -1;
	if (prog->ph[0].nb_philos == 1)
		pthread_create(&prog->ph[0].th, NULL, &routine_solo, &prog->ph[0]);
	else
	{
		while (++i < nb_philo)
			pthread_create(&prog->ph[i].th, NULL, &routine, &prog->ph[i]);
	}
	i = -1;
	if (pthread_create(&monitor, NULL, &monitoring, prog->ph) != 0)
		perror("pthread create error\n");
	if (pthread_join(monitor, NULL) != 0)
		perror("pthread join error\n");
	while (++i < nb_philo)
		if (pthread_join(prog->ph[i].th, NULL) != 0)
	i = -1;
	while (++i < nb_philo)
		pthread_mutex_destroy(&forks[i]);
}
