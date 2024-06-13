/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:47:08 by eperperi          #+#    #+#             */
/*   Updated: 2024/06/13 13:47:18 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_args(int argc, char **argv, t_data *data);
int init_mutexes(t_data *data);
void init_philosophers(t_data *data);

void leaks()
{
	system("leaks philo");
}

int main (int argc, char **argv)
{
	t_data data;
	

	atexit(&leaks);
	if (argc != 5 && argc != 6 )
	{
		printf("Not the right amount of arguments!\n");
		return (0);
	}

	if (init_args(argc, argv, &data) != 0)
	{
		printf("Not correct arguments so the program to run!\n");
		return (0);
	}
	if (init_mutexes(&data) != 0)
	{
		printf("Fatal error when intializing mutex\n");
		return (0);
	}
	init_philosophers(&data);
	if (threads(&data) != 0)
	{
		printf("Fatal error when creating the threads\n");
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
	data->dead = 0;
	data->all_ate = 0;
	data->first_timestamp = get_time();
	data->philosophers = malloc(sizeof(t_philosopher) * data->number_of_philo);
	if (data->philosophers == NULL)
		return (1);
	data->forks = malloc(sizeof(t_philosopher) * data->number_of_philo);
	if (data->forks == NULL)
		return (1);
	if (argc == 6)
	{
		data->times_to_eat = ft_atoi(argv[5]);
		if (data->times_to_eat <= 0)
			return (1);
	}
	if (data->number_of_philo < 2 || data->number_of_philo >= 250 || data->time_to_die <= 0
		|| data->time_to_eat <= 0|| data->time_to_sleep <= 0)
		return (1);
	return (0);
}
int init_mutexes(t_data *data)
{
    int i;

    i = 0;
    while (i < data->number_of_philo)
    {
        if (pthread_mutex_init(&(data->forks[i]), NULL))
        {
            printf("Failed to initialize fork mutex %d\n", i);
			while (i > 0)
                pthread_mutex_destroy(&(data->forks[--i]));
            free(data->forks);
            return (1);
        }
        i++;
    }
    if (pthread_mutex_init(&(data->printing), NULL) != 0)
    {
        printf("Failed to initialize printing mutex\n");
		while (--i >= 0)
            pthread_mutex_destroy(&(data->forks[i]));
        free(data->forks);
        return (1);
    }
    if (pthread_mutex_init(&(data->moves_check), NULL))
    {
        printf("Failed to initialize moves_check mutex\n");
		pthread_mutex_destroy(&(data->printing));
        while (--i >= 0)
            pthread_mutex_destroy(&(data->forks[i]));
        free(data->forks);
        return (1);
    }
    return (0);
}
void init_philosophers(t_data *data)
{
	t_philosopher *philos;
	int i;

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
		i++;
	}
}