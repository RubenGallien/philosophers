/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:07:38 by rgallien          #+#    #+#             */
/*   Updated: 2024/07/09 17:17:12 by rgallien         ###   ########.fr       */
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
	t_philo		*philos;
	size_t		i;

	i = 0;
	philos = (t_philo *)args;
	while (1)
	{
		if (meal_too_late(philos))
			break ;
		if (philos[0].must_eat > 0 && eat_enough(philos))
		{
			while (i < philos[0].nb_philos)
			{
				pthread_mutex_lock(philos[0].m_dead);
				philos[i].is_dead = 1;
				pthread_mutex_unlock(philos[0].m_dead);
				i++;
			}
			break ;
		}
		usleep(1000);
	}
	return (philos);
}

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->id % 2)
		ft_usleep(philo->time_eat / 2, philo);
	while (!ft_is_dead(philo))
	{
		if (!(philo->id % 2))
			ft_eat(philo, philo->l_fork, philo->r_fork);
		else
			ft_eat(philo, philo->r_fork, philo->l_fork);
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
		pthread_join(prog->ph[i].th, NULL);
	i = -1;
	while (++i < nb_philo)
		pthread_mutex_destroy(&forks[i]);
}
