/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aproust <aproust@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:14:29 by pdosso-d          #+#    #+#             */
/*   Updated: 2023/05/12 12:20:07 by aproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct s_data
{
	int				np;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meal;
	int				dead;
	int				finish;
	long			start_time;
	pthread_mutex_t	last_eat;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
	pthread_mutex_t	finished;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				count_meal;
	long			last_eat_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	fork;
	pthread_t		philo;
	t_data			*data;
}	t_philo;

long	get_time(void);
int		is_dead(t_data *data);
void	ft_usleep(long ms, t_data *data);
long	current_time(t_philo *philo);
int		print(t_philo *philo, char *s);
long	ft_atoll(const char *str);
t_philo	*init_philo(t_data *data);
int		parsing(t_data *data, int ac, char **av);
int		check_pos_int(char **argv);
int		parsing(t_data *data, int ac, char **av);
int		when_forks_are_taken(t_philo *philo);
void	*thread(void *data);
void	exec_thread(t_data *data, t_philo *philo);

#endif
