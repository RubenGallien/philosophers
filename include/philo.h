/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:51:31 by rgallien          #+#    #+#             */
/*   Updated: 2024/06/24 20:12:12 by rgallien         ###   ########.fr       */
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
	size_t			last_meal;
	size_t			start;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_t		th;
	int				must_eat;
	int				is_dead;
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
void	make_threads(t_prog *prog, long nb_philo, pthread_mutex_t *forks);
size_t	time_now(size_t	start);
// init
void	ft_init(t_prog *prog, char *argv[], pthread_mutex_t *forks);

#endif