/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:14:56 by rgallien          #+#    #+#             */
/*   Updated: 2024/06/20 17:26:34 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals_eaten;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				num_of_philos;
	int				num_times_to_eat;
}					t_philo;

typedef struct s_program
{
	t_philo			*ph;
	pthread_mutex_t mutex;
}					t_program;

int		check_args(char **argv, t_program *philos);
void	ft_free_philos(t_program *philos, int i);
int		create_threads(t_program *philos, int nb);
long	ft_atol(char *str);
size_t	ft_strlen(char *str);

#endif