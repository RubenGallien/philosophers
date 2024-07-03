/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dead.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:36:54 by rgallien          #+#    #+#             */
/*   Updated: 2024/07/03 18:02:05 by rgallien         ###   ########.fr       */
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

int meal_too_late(t_philo *philos)
{
    size_t i;

    i = 0;
    while (i < philos[0].nb_philos)
    {
        pthread_mutex_lock(philos[i].m_meal);
        if ((get_current_time() - philos[i].last_meal) >= philos[0].time_die)
        {
			pthread_mutex_unlock(philos[i].m_meal);
            ft_print(&philos[i], "died");
			i = 0;
            while (i < philos[0].nb_philos)
            {
                pthread_mutex_lock(philos[i].m_dead);
                philos[i].is_dead = 1;
                pthread_mutex_unlock(philos[i].m_dead);
				i++;
            }
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
		if (philos[0].must_eat > 0 && philos[i].nb_eat >= philos[0].must_eat)
			i++;
		else
			return (0);
	}
	--i;
	while (i > 0)
	{
		pthread_mutex_lock(philos[0].m_dead);
		philos[i].is_dead = 1;
		pthread_mutex_unlock(philos[0].m_dead);
		if (i == 0)
			return (0);
		i--;
	}
	return (0);
}
