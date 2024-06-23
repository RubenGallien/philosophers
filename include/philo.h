/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:51:31 by rgallien          #+#    #+#             */
/*   Updated: 2024/06/23 19:07:05 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>

typedef struct t_philo
{
	int				id;
	size_t			nb_philos;
	size_t			time_die;
	size_t			time_eat;
	size_t			time_sleep;
	int				must_eat;
	size_t			start;
	size_t			last_meal;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_t		th;
}			t_philo;

typedef struct s_prog
{
	t_philo	*ph;
}			t_prog;

// parsing
int		check_args(char *argv[]);
long	ft_atol(char *str);

// utils
size_t	get_current_time(void);
int		ft_usleep(size_t milliseconds);

// init
void	ft_init(t_prog *prog, char *argv[]);

#endif