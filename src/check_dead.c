/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dead.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:36:54 by rgallien          #+#    #+#             */
/*   Updated: 2024/07/09 17:30:11 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->m_dead);
	if (philo->is_dead)
	{
		pthread_mutex_unlock(philo->m_dead);
		return (1);
	}
	pthread_mutex_unlock(philo->m_dead);
	return (0);
}

int	meal_too_late(t_philo *philos)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < philos[0].nb_philos)
	{
		pthread_mutex_lock(philos[i].m_meal);
		if ((get_current_time() - philos[i].last_meal) >= philos[0].time_die)
		{
			pthread_mutex_unlock(philos[i].m_meal);
			j = 0;
			while (j < philos[0].nb_philos)
			{
				pthread_mutex_lock(philos[j].m_dead);
				philos[j].is_dead = 1;
				pthread_mutex_unlock(philos[j].m_dead);
				j++;
			}
			printf("%ld %d died\n", time_now(philos[i].start), philos[i].id);
			return (1);
		}
		pthread_mutex_unlock(philos[i].m_meal);
		i++;
	}
	return (0);
}

int	eat_enough(t_philo *philos)
{
	size_t	i;

	i = 0;
	while (i < philos[0].nb_philos)
	{
		pthread_mutex_lock(philos[0].m_eat);
		if (philos[i].nb_eat >= philos[0].must_eat)
		{
			pthread_mutex_unlock(philos[0].m_eat);
			i++;
		}
		else
		{
			pthread_mutex_unlock(philos[0].m_eat);
			return (0);
		}
	}
	return (1);
}
