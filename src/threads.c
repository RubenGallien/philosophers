/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:07:38 by rgallien          #+#    #+#             */
/*   Updated: 2024/06/28 22:04:49 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitoring(void *args)
{
	t_philo	*philos;
	size_t	i;

	i = 0;
	philos = (t_philo*)args;
	while (1)
	{
		i = 0;
		while (i < philos[0].nb_philos)
		{
			if ((get_current_time() - philos[i].last_meal) > philos[0].time_die)
			{
				printf("%ld %d died\n", time_now(philos[i].start), philos[i].id);
				i = 0;
				while (i < philos[0].nb_philos)
				{
					philos[i].is_dead = 1;
					i++;
				}
				return (NULL);
			}
			if (philos[i].must_eat > 0 && philos[i].nb_eat >= philos[i].must_eat)
			{
				printf("all eating\n");
				i = 0;
				while (i < philos[0].nb_philos)
				{
					philos[i].is_dead = 1;
					i++;
				}
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->id % 2 == 0)
		ft_usleep(1, philo);
	while (!philo->is_dead)
	{
		pthread_mutex_lock(philo->l_fork);
		printf("%ld %d has taken a fork\n", time_now(philo->start), philo->id);
		pthread_mutex_lock(philo->r_fork);
		printf("%ld %d has taken a fork\n", time_now(philo->start), philo->id);
		printf("%ld %d is eating\n", time_now(philo->start), philo->id);
		ft_usleep(philo->time_eat, philo);
		philo->last_meal = get_current_time();
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		philo->nb_eat++;
		printf("%ld %d is sleeping\n", time_now(philo->start), philo->id);
		ft_usleep(philo->time_sleep, philo);
		printf("%ld %d is thinking\n", time_now(philo->start), philo->id);
	}
	return (NULL);
}

void	make_threads(t_prog *prog, long nb_philo, pthread_mutex_t *forks)
{
	long		i;
	pthread_t	monitor;

	i = -1;
	while (++i < nb_philo)
	{
		if(pthread_create(&prog->ph[i].th, NULL, &routine, &prog->ph[i]) != 0)
			perror("philos create error\n");
	}
	i = -1;
	if (pthread_create(&monitor, NULL, &monitoring, prog->ph) != 0)
		perror("pthread create error\n");
	if (pthread_join(monitor, NULL) != 0)
		perror("pthread join error\n");
	while (++i < nb_philo)
	{
		if (pthread_join(prog->ph[i].th, NULL) != 0)
			perror("philos join error\n");
	}
	i = -1;
	while (++i < nb_philo)
		pthread_mutex_destroy(&forks[i]);
}
