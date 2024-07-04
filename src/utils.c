/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 18:32:55 by rgallien          #+#    #+#             */
/*   Updated: 2024/07/04 11:26:19 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] == s2[i])
			i++;
		else
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
	}
	return (0);
}

void	ft_print(t_philo *philo, char *step)
{
	pthread_mutex_lock(philo->m_dead);
	pthread_mutex_lock(philo->m_print);
	if (!ft_strncmp(step, "died", ft_strlen(step)) && !philo->is_dead)
		printf("%ld %d died\n", time_now(philo->start), philo->id);
	if (!ft_strncmp(step, "fork", ft_strlen(step)) && !philo->is_dead)
		printf("%ld %d has taken a fork\n", time_now(philo->start), philo->id);
	if (!ft_strncmp(step, "eat", ft_strlen(step)) && !philo->is_dead)
	{
		pthread_mutex_lock(philo->m_eat);
		philo->nb_eat++;
		pthread_mutex_unlock(philo->m_eat);
		printf("%ld %d is eating\n", time_now(philo->start), philo->id);
	}
	if (!ft_strncmp(step, "sleep", ft_strlen(step)) && !philo->is_dead)
		printf("%ld %d is sleeping\n", time_now(philo->start), philo->id);
	if (!ft_strncmp(step, "think", ft_strlen(step)) && !philo->is_dead)
		printf("%ld %d is thinking\n", time_now(philo->start), philo->id);
	pthread_mutex_unlock(philo->m_print);
	pthread_mutex_unlock(philo->m_dead);
}

size_t	time_now(size_t	start)
{
	return (get_current_time() - start);
}

int	ft_usleep(size_t milliseconds, t_philo *philo)
{
	size_t	start;

	(void)*philo;
	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
