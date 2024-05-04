/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aproust <aproust@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:17:26 by aproust           #+#    #+#             */
/*   Updated: 2023/05/12 12:22:25 by aproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	is_dead(t_data *data)
{
	int	dead;

	pthread_mutex_lock(&data->death);
	dead = data->dead;
	pthread_mutex_unlock(&data->death);
	return (dead);
}

void	ft_usleep(long ms, t_data *data)
{
	long	begin;

	begin = get_time();
	while (get_time() - begin < ms)
	{
		if (is_dead(data) == 1)
			return ;
		usleep(10);
	}
}

long	current_time(t_philo *philo)
{
	return (get_time() - philo->data->start_time);
}

int	print(t_philo *philo, char *s)
{
	pthread_mutex_lock(&philo->data->print);
	if (is_dead(philo->data))
	{
		pthread_mutex_unlock(&philo->data->print);
		return (1);
	}
	printf("%ld %d %s\n", current_time(philo), philo->id + 1, s);
	pthread_mutex_unlock(&philo->data->print);
	return (0);
}
