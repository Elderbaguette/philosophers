/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aproust <aproust@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:26:18 by aproust           #+#    #+#             */
/*   Updated: 2023/05/12 13:01:09 by aproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	when_forks_are_taken(t_philo *philo)
{
	if (print(philo, "is eating"))
		return (pthread_mutex_unlock(philo->left_fork),
			pthread_mutex_unlock(philo->right_fork), 1);
	pthread_mutex_lock(&philo->data->last_eat);
	philo->last_eat_time = get_time();
	pthread_mutex_unlock(&philo->data->last_eat);
	philo->count_meal++;
	if (philo->count_meal == philo->data->nb_meal)
	{
		pthread_mutex_lock(&philo->data->finished);
		philo->data->finish++;
		pthread_mutex_unlock(&philo->data->finished);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	ft_usleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (print(philo, "is sleeping"))
		return (1);
	ft_usleep(philo->data->time_to_sleep, philo->data);
	if (print(philo, "is thinking"))
		return (1);
	return (0);
}

int	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		if (print(philo, "has taken a fork"))
			return (pthread_mutex_unlock(philo->left_fork), 1);
		pthread_mutex_lock(philo->right_fork);
		if (print(philo, "has taken a fork"))
			return (pthread_mutex_unlock(philo->right_fork), 1);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		if (print(philo, "has taken a fork"))
			return (pthread_mutex_unlock(philo->right_fork), 1);
		pthread_mutex_lock(philo->left_fork);
		if (print(philo, "has taken a fork"))
			return (pthread_mutex_unlock(philo->left_fork), 1);
	}
	return (0);
}

void	*thread(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat * 0.25, philo->data);
	while (!is_dead(philo->data))
	{
		if (philo->data->np % 2 && philo->count_meal)
			ft_usleep(philo->data->time_to_die * 0.2, philo->data);
		if (take_fork(philo))
			return (NULL);
		if (when_forks_are_taken(philo))
			return (NULL);
	}
	return (NULL);
}

int	is_finish(int eating_time, t_data *data, int j)
{
	int	finished;

	if (eating_time >= data->time_to_die)
	{
		pthread_mutex_lock(&data->death);
		data->dead = 1;
		pthread_mutex_unlock(&data->death);
		pthread_mutex_lock(&data->print);
		printf("%ld %d died\n", get_time() - data->start_time, j + 1);
		pthread_mutex_unlock(&data->print);
		return (1);
	}
	pthread_mutex_lock(&data->finished);
	finished = data->finish;
	pthread_mutex_unlock(&data->finished);
	if (finished == data->np)
	{
		pthread_mutex_lock(&data->death);
		data->dead = 1;
		pthread_mutex_unlock(&data->death);
		return (1);
	}
	return (0);
}

void	exec_thread(t_data *data, t_philo *philo)
{
	int		j;
	long	eating_time;

	while (1)
	{
		j = 0;
		while (j < data->np)
		{
			pthread_mutex_lock(&data->last_eat);
			eating_time = get_time() - philo[j].last_eat_time;
			pthread_mutex_unlock(&data->last_eat);
			if (is_finish(eating_time, data, j))
				return ;
			j++;
		}
		usleep(100);
	}
}
