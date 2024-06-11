/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:47:41 by eperperi          #+#    #+#             */
/*   Updated: 2024/06/11 12:04:12 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>


typedef struct s_philosopher
{
	int				id;
	int				times_ate;
	int				left_fork;
	int				right_fork;
	long long		last_meal_time;
	struct s_data	*data;
	pthread_t		thread_id;
	
} t_philosopher;

typedef struct s_data
{
	int				number_of_philo;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_to_eat;
	int				time_to_die;
	int				dead;
	long long		first_timestamp;
	pthread_mutex_t	forks[250];
	pthread_mutex_t	moves_check;
	t_philosopher	philosophers[250];
	pthread_mutex_t	printing;
} t_data;


int			ft_atoi(const char *str);
long long	get_time(void);
void		ft_usleep(long long time, t_data *data);
int			threads(t_data *data);
void *routine(void *temp_philo);

#endif