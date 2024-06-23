/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:52:30 by rgallien          #+#    #+#             */
/*   Updated: 2024/06/23 19:07:29 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_prog	prog;

	if (argc < 5 || argc > 6 || !check_args(argv))
		return (printf("Error, Wrong args\n"), 0);
	ft_init(&prog, ++argv);
	make_thread(prog);
	return (printf("Ok\n"), 1);
}
