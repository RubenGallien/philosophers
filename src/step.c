/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:50:14 by rgallien          #+#    #+#             */
/*   Updated: 2024/07/02 17:29:55 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->m_dead);
	if (!philo->is_dead)
	{
		pthread_mutex_unlock(philo->m_dead);
		pthread_mutex_lock(philo->l_fork);
		ft_print(philo, "fork");
		pthread_mutex_lock(philo->r_fork);
		ft_print(philo, "fork");
		ft_print(philo, "eat");
		philo->nb_eat++;
		philo->last_meal = get_current_time();
		ft_usleep(philo->time_eat, philo);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
	else
		pthread_mutex_unlock(philo->m_dead);
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
	}
	else
		pthread_mutex_unlock(philo->m_dead);
	return (0);
}
