/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:50:14 by rgallien          #+#    #+#             */
/*   Updated: 2024/07/09 13:50:15 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_eat(t_philo *philo, pthread_mutex_t *first, pthread_mutex_t *second)
{
	if (!ft_is_dead(philo))
	{
		pthread_mutex_lock(first);
		ft_print(philo, "fork");
		pthread_mutex_lock(second);
		ft_print(philo, "fork");
		ft_print(philo, "eat");
		pthread_mutex_lock(philo->m_meal);
		philo->last_meal = get_current_time();
		pthread_mutex_unlock(philo->m_meal);
		ft_usleep(philo->time_eat, philo);
		pthread_mutex_unlock(second);
		pthread_mutex_unlock(first);
	}
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->m_dead);
	if (!philo->is_dead)
	{
		pthread_mutex_unlock(philo->m_dead);
		ft_print(philo, "sleep");
		ft_usleep(philo->time_sleep, philo);
	}
	else
		pthread_mutex_unlock(philo->m_dead);
	return (0);
}

int	ft_think(t_philo *philo)
{
	pthread_mutex_lock(philo->m_dead);
	if (!philo->is_dead)
	{
		pthread_mutex_unlock(philo->m_dead);
		ft_print(philo, "think");
		if (philo->nb_philos % 2 && philo->time_eat >= philo->time_sleep)
			ft_usleep(philo->time_eat - philo->time_sleep + 2, philo);
		else
			usleep(1000);
	}
	else
		pthread_mutex_unlock(philo->m_dead);
	return (0);
}
