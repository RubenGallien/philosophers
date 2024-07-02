/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:07:38 by rgallien          #+#    #+#             */
/*   Updated: 2024/07/02 17:32:02 by rgallien         ###   ########.fr       */
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

int	checking(t_philo *philos, size_t i)
{
	if ((get_current_time() - philos[i].last_meal) > philos[0].time_die)
	{
		ft_print(&philos[i], "died");
		i = -1;
		while (++i < philos[0].nb_philos)
		{
			pthread_mutex_lock(philos->m_dead);
			philos[i].is_dead = 1;
			pthread_mutex_unlock(philos->m_dead);
		}
		return (1);
	}
	i = 0;
	while (i < philos[0].nb_philos)
	{
		if (philos[0].must_eat > 0 && philos[i].nb_eat >= philos[0].must_eat)
			i++;
		else
			return (0);
	}
	--i;
	while (i > 0)
	{
		pthread_mutex_lock(philos->m_dead);
		philos[i].is_dead = 1;
		pthread_mutex_unlock(philos->m_dead);
		if (i == 0)
			return (1);
		i--;
	}
	return (1);
}

void	*monitoring(void *args)
{
	t_philo	*philos;
	size_t	i;

	i = 0;
	philos = (t_philo *)args;
	while (1)
	{
		i = 0;
		while (i < philos[0].nb_philos)
		{
			if (checking(philos, i))
				return (NULL);
			i++;
		}
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
	while (!philo->is_dead)
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
