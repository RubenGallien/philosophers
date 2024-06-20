/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:55:11 by rgallien          #+#    #+#             */
/*   Updated: 2024/06/20 17:59:21 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine(void *arg)
{
	(void)arg;
	pthread_mutex_t *mutex = (pthread_mutex_t*)arg;
	pthread_mutex_lock(mutex);
	printf("Bonjour\n");
	pthread_mutex_unlock(mutex);
	return (0);
}


int	create_threads(t_program *philos, int nb)
{
	int	i;

	i = -1;
	while (++i < nb)
	{
		if (pthread_create(&philos->ph[i].thread, NULL, &routine, &philos->mutex) != 0)
			return (perror("Failed to create thread"), 1);
		usleep(1);
	}
	i = -1;
	while (++i < nb)
	{
		if (pthread_join(philos->ph[i].thread, NULL))
			return (2);
		printf("Thread %d has finished execution\n", i + 1);
	}
	return (1);
}
