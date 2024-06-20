/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:47:08 by eperperi          #+#    #+#             */
/*   Updated: 2024/06/20 16:20:26 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		init_args(int argc, char **argv, t_data *data);
int		init_mutexes(t_data *data);
int		init_philosophers(t_data *data);
void	mutex_error(t_data *data);
int		keep_init(t_data *data);
int		check_for_one(t_data *data);

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
	{
		printf("Not the right amount of arguments!\n");
		return (0);
	}
	if (init_args(argc, argv, &data) != 0)
	{
		printf("Not correct arguments so the program to run!\n");
		return (0);
	}
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

int	check_for_one(t_data *data)
{
	int				i;

	i = 0;
	if (data->number_of_philo == 1)
	{
		printing_move(data, 1, UNDERLINE BOLD RED "PHILO DIED" RESET);
		while (i < data->number_of_philo)
		{
			pthread_mutex_destroy(&(data->philosophers[i].last_meal_mutex));
			i++;
		}
		return (1);
	}
	return (0);
}

int	init_args(int argc, char **argv, t_data *data)
{
	data->number_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->flag_dead = 0;
	data->flag_all_ate = 0;
	data->first_timestamp = get_time();
	data->philosophers = malloc(sizeof(t_philosopher) * data->number_of_philo);
	if (data->philosophers == NULL)
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philo);
	if (data->forks == NULL)
		return (1);
	if (argc == 6)
	{
		data->times_to_eat = ft_atoi(argv[5]);
		if (data->times_to_eat <= 0)
			return (1);
	}
	else
		data->times_to_eat = -1;
	if (data->number_of_philo < 1 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
		return (1);
	return (0);
}

int	init_mutexes(t_data *data)
{
	int				i;

	i = 0;
	while (i < data->number_of_philo)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL) != 0)
			return (mutex_error(data), 1);
		i++;
	}
	if (pthread_mutex_init(&(data->printing), NULL) != 0)
		return (pthread_mutex_destroy(&(data->printing)),
			mutex_error(data), 1);
	if (pthread_mutex_init(&(data->moves_check), NULL) != 0)
		return (pthread_mutex_destroy(&(data->moves_check)),
			pthread_mutex_destroy(&(data->printing)), mutex_error(data), 1);
	if (pthread_mutex_init(&(data->flag_dead_mutex), NULL) != 0)
		return (pthread_mutex_destroy(&(data->flag_dead_mutex)),
			pthread_mutex_destroy(&(data->moves_check)),
			pthread_mutex_destroy(&(data->printing)), mutex_error(data), 1);
	if (keep_init(data))
		return (1);
	return (0);
}

int	keep_init(t_data *data)
{
	if (pthread_mutex_init(&(data->times_ate_mutex), NULL) != 0)
		return (pthread_mutex_destroy(&(data->times_ate_mutex)),
			pthread_mutex_destroy(&(data->flag_dead_mutex)),
			pthread_mutex_destroy(&(data->moves_check)),
			pthread_mutex_destroy(&(data->printing)),
			mutex_error(data), 1);
	if (pthread_mutex_init(&(data->flag_ate_mutex), NULL) != 0)
		return (pthread_mutex_destroy(&(data->flag_ate_mutex)),
			pthread_mutex_destroy(&(data->times_ate_mutex)),
			pthread_mutex_destroy(&(data->flag_dead_mutex)),
			pthread_mutex_destroy(&(data->moves_check)),
			pthread_mutex_destroy(&(data->printing)),
			mutex_error(data), 1);
	return (0);
}

int	init_philosophers(t_data *data)
{
	t_philosopher	*philos;
	int				i;

	philos = data->philosophers;
	i = 0;
	while (i < data->number_of_philo)
	{
		philos[i].id = i + 1;
		philos[i].times_ate = 0;
		philos[i].left_fork = i;
		philos[i].right_fork = (i + 1) % data->number_of_philo;
		philos[i].last_meal_time = 0;
		philos[i].data = data;
		if (pthread_mutex_init(&(philos[i].last_meal_mutex), NULL) != 0)
		{
			while (i >= 0)
			{
				pthread_mutex_destroy(&(data->philosophers[i].last_meal_mutex));
				i--;
			}
			return (1);
		}
		i++;
	}
	return (0);
}

void	mutex_error(t_data *data)
{
	int	i;

	i = 0;
	printf("Failed to initialize mutexes\n");
	while (i < data->number_of_philo)
	{
		pthread_mutex_destroy(&(data->forks[i]));
		pthread_mutex_destroy(&(data->philosophers[i].last_meal_mutex));
		i++;
	}
	free(data->forks);
	free(data->philosophers);
}
