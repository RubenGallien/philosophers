/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:52:30 by rgallien          #+#    #+#             */
/*   Updated: 2024/06/24 03:52:13 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_prog			prog;
	pthread_mutex_t	*forks;

	if (argc < 5 || argc > 6 || !check_args(argv))
		return (printf("Error, Wrong args\n"), 0);
	forks = malloc(sizeof(pthread_mutex_t) * ft_atol(argv[1]));
	if (!forks)
		perror("init of forks failed\n");
	ft_init(&prog, ++argv, forks);
	make_threads(&prog, ft_atol(argv[0]), forks);
	free(prog.ph);
	free(forks);
	return (1);
}
