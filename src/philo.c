/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:14:10 by rgallien          #+#    #+#             */
/*   Updated: 2024/06/20 17:36:46 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char *argv[])
{
	t_program	philos;
	int			i;

	if (argc < 5 || argc > 6 || !check_args(argv, &philos))
		return (1);
	create_threads(&philos, ft_atol(argv[1]));

	i = 0;
	return (0);
}