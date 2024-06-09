/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:47:08 by eperperi          #+#    #+#             */
/*   Updated: 2024/06/09 17:34:44 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_args(int argc, char **argv, t_data *data);

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
	if (!(init_args(argc, argv, &data)))
	{
		printf("Not correct arguments so the program to run!\n");
		return (0);
	}
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
			return (0);
	}
	if (data->number_of_philo < 2 || data->time_to_die <= 0 || data->time_to_eat <= 0
		|| data->time_to_sleep <= 0)
		return (0);
	return (1);
}
