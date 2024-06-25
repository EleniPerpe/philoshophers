/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:47:08 by eperperi          #+#    #+#             */
/*   Updated: 2024/06/25 13:49:33 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		check_for_one(t_data *data);
int		check_args(int argc, char **argv);
int		check_for_arg_nums(t_data *data);

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
	{
		printf("Not the right amount of arguments!\n");
		return (0);
	}
	if (check_args(argc, argv))
		return (printf("Characters are not allowed\n"), 0);
	if (init_args(argc, argv, &data) != 0)
	{
		printf("Not correct amount of arguments so the program to run!\n");
		return (free(data.philosophers), free(data.forks), 0);
	}
	if (check_for_arg_nums(&data) != 0)
		return (1);
	if (init_philosophers(&data) != 0)
		return (printf("Fatal error when intializing mutex\n"), 0);
	if (check_for_one(&data) != 0)
		return (1);
	if (init_mutexes(&data) != 0)
		return (printf("Fatal error when intializing mutex\n"), 0);
	if (threads(&data) != 0)
		return (printf("Fatal error when creating the threads\n"), 0);
	return (1);
}

int	check_for_arg_nums(t_data *data)
{
	if (data->number_of_philo > 200)
	{
		printf("The number of philosophers can not be more than 200!\n");
		return (free(data->philosophers), free(data->forks), 1);
	}
	if (data->time_to_die < 60 || data->time_to_eat < 60
		|| data->time_to_sleep < 60)
	{
		printf("None of the times can be less than 60!\n");
		return (free(data->philosophers), free(data->forks), 1);
	}
	return (0);
}

int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_for_one(t_data *data)
{
	int				i;

	i = 0;
	if (data->number_of_philo == 1)
	{
		printf(LIGHT_YELLOW "0 " RESET "1 %s\n",
			MAGENTA "has taken a fork" RESET);
		printf(LIGHT_YELLOW "%d " RESET "1 %s\n",
			data->time_to_die, UNDERLINE BOLD RED "PHILO DIED" RESET);
		while (i < data->number_of_philo)
		{
			pthread_mutex_destroy(&(data->philosophers[i].last_meal_mutex));
			i++;
		}
		free(data->philosophers);
		free(data->forks);
		return (1);
	}
	return (0);
}
