/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sequel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aproust <aproust@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:23:14 by aproust           #+#    #+#             */
/*   Updated: 2023/05/12 12:19:27 by aproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoll(const char *str)
{
	long long	i;
	long long	j;
	long long	l;

	i = 0;
	j = 0;
	l = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			j = 1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		l = l * 10 + str[i] - '0';
		i++;
	}
	if (j == 1)
		return (-l);
	return (l);
}

int	check_pos_int(char **argv)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (argv[++j])
	{
		if (argv[j][0] == '-' || argv[j][0] == '+')
			i++;
		while (argv[j][++i])
		{
			if (argv[j][i] < '0' || argv[j][i] > '9')
				return (1);
		}
		if (ft_atoll(argv[j]) > 2147483647
			|| ft_atoll(argv[j]) < 0)
			return (1);
		i = -1;
	}
	return (0);
}

int	parsing(t_data *data, int ac, char **av)
{
	data->np = atoi(av[1]);
	data->time_to_die = atoi(av[2]);
	data->time_to_eat = atoi(av[3]);
	data->time_to_sleep = atoi(av[4]);
	data->nb_meal = -1;
	if (ac == 6)
		data->nb_meal = atoi(av[5]);
	if (data->np == 1)
	{
		printf("0 1 take a fork\n");
		ft_usleep(data->time_to_die, data);
		printf("%d 1 take a fork\n", data->time_to_die);
		return (1);
	}
	return (0);
}

void	create_philo(t_data *data, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < data->np)
	{
		pthread_mutex_init(&philos[i].fork, NULL);
		philos[i].left_fork = &philos[i].fork;
		if (i != data->np - 1)
			philos[i].right_fork = &philos[i + 1].fork;
		else
			philos[i].right_fork = &philos[0].fork;
	}
	i = -1;
	while (++i < data->np)
	{
		philos[i].last_eat_time = get_time();
		philos[i].id = i;
		philos[i].data = data;
		pthread_create(&philos[i].philo, NULL, thread, (void *)&philos[i]);
	}
}

t_philo	*init_philo(t_data *data)
{
	t_philo	*philos;
	int		i;

	i = -1;
	data->start_time = get_time();
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->death, NULL);
	pthread_mutex_init(&data->finished, NULL);
	philos = calloc(sizeof(t_philo), data->np);
	create_philo(data, philos);
	return (philos);
}
