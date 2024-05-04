/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aproust <aproust@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:13:53 by pdosso-d          #+#    #+#             */
/*   Updated: 2023/05/12 11:45:43 by aproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*	np = Number of Philosophers			pata = Philosopher Data				  */
/*	notepme =	Number of Times Each Philosopher Must Eat					  */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	int				i;
	static t_data	data = {0};
	t_philo			*philos;

	i = -1;
	if (!(ac >= 5 && ac <= 6))
	{
		write(2, "Error\n", 6);
		return (1);
	}
	if (check_pos_int(av) == 1)
		return (write(2, "Error\n", 6));
	if (parsing(&data, ac, av))
		return (0);
	philos = init_philo(&data);
	exec_thread(&data, philos);
	while (++i < data.np)
	{
		pthread_join(philos[i].philo, NULL);
	}
	free(philos);
}
/*

./philo 4 410 200 200 VIVENT // pair
./philo 5 610 200 200 VIVENT // impair
./philo 4 399 200 200 MEURENT // pair
./philo 5 599 200 200 MEURENT // impair

*/
