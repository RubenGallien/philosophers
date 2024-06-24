/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:07:38 by rgallien          #+#    #+#             */
/*   Updated: 2024/06/24 20:18:57 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitoring()
{
	printf("ok je suis le monitor\n");
	return (NULL);
}

void	*routine(void *args)
{
	t_philo	philo;

	philo = *(t_philo *)args;
	if (philo.id % 2 == 0)
		ft_usleep(1);
	while (!philo.is_dead)
	{
		pthread_mutex_lock(philo.l_fork);
		printf("%ld %d has taken a fork\n", time_now(philo.start), philo.id);
		pthread_mutex_lock(philo.r_fork);
		printf("%ld %d has taken a fork\n", time_now(philo.start), philo.id);
		printf("%ld %d is eating\n", time_now(philo.start), philo.id);
		ft_usleep(philo.time_eat);
		pthread_mutex_unlock(philo.r_fork);
		pthread_mutex_unlock(philo.l_fork);
		printf("%ld %d is sleeping\n", time_now(philo.start), philo.id);
		ft_usleep(philo.time_sleep);
		printf("%ld %d is thinking\n", time_now(philo.start), philo.id);
	}
	return (NULL);
}

void	make_threads(t_prog *prog, long nb_philo, pthread_mutex_t *forks)
{
	long		i;
	pthread_t	monitor;

	i = -1;
	while (++i < nb_philo)
		pthread_create(&prog->ph[i].th, NULL, &routine, &prog->ph[i]);
	if (!pthread_create(&monitor, NULL, &monitoring, NULL))
		perror("bon\n");
	i = -1;
	while (++i < nb_philo)
		pthread_join(prog->ph[i].th, NULL);
	if (!pthread_join(monitor, NULL))
		perror("bon\n");
	i = -1;
	while (++i < nb_philo)
		pthread_mutex_destroy(&forks[i]);
}
