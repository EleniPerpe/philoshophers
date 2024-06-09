/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:47:08 by eperperi          #+#    #+#             */
/*   Updated: 2024/06/09 18:19:11 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_args(int argc, char **argv, t_data *data);
int init_mutexes(t_data *data);

int main (int argc, char **argv)
{
	t_data data;
	
	(void)argv;
	if (argc != 5 && argc != 6 )
	{
		printf("Not the right amount of arguments!\n");
		return (0);
	}
	memset(&data, 0, sizeof(data));
	if (init_args(argc, argv, &data))
	{
		if (init_args(argc, argv, &data) == 1)
			printf("Not correct arguments so the program to run!\n");
		if (init_args(argc, argv, &data) == 2)
			printf("Fatal error when intializing mutex\n");	
		return (0);
	}
	return (1);
}

int init_args(int argc, char **argv, t_data *data)
{
	data->number_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		data->times_to_eat = ft_atoi(argv[5]);
		if (data->times_to_eat <= 0)
			return (1);
	}
	if (data->number_of_philo < 2 || data->number_of_philo >= 250 || data->time_to_die <= 0
		|| data->time_to_eat <= 0|| data->time_to_sleep <= 0)
		return (1);
	if (!(init_mutexes(data)))
		return (2);
	return (0);
}
int init_mutexes(t_data *data)
{
	int i;

	i = 0;
	while (i < data->number_of_philo)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL))
			return (0);
		i++;
	}
	if (pthread_mutex_init(&(data->printing), NULL))
		return (0);
	return (1);
}