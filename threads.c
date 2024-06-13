/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:49:54 by eperperi          #+#    #+#             */
/*   Updated: 2024/06/13 14:14:57 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine(void *temp_philo);
void printing_move(t_data *data, int philo_id, char *string);
void eating_time(t_philosopher *philo);
void finish_program(t_data *data, t_philosopher *philo);
void	check_for_deads(t_data *data,t_philosopher *philo);

int threads(t_data *data)
{
	int i;
	t_philosopher *philo;

	i = 0;
	philo = data->philosophers;
	while (i < data->number_of_philo)
	{
		if (pthread_create(&(philo[i].thread_id), NULL, routine, &(philo[i])))
			return (3);
		philo[i].last_meal_time = get_time();
		i++;
	}
	check_for_deads(data, philo);
	finish_program(data, philo);
	return (0);
}

void *routine(void *temp_philo)
{
	t_philosopher *philo;
	t_data *data;
	
	philo = (t_philosopher *)temp_philo;
	data = philo->data;
	if (philo->id % 2)
		usleep(15000);
	while (data->flag_dead == 0)
	{
		eating_time(philo);
		if (data->flag_all_ate)
			break ;
		printing_move(data, philo->id, "is sleeping");
		ft_usleep(data->time_to_sleep, data);
		printing_move(data, philo->id, "is thinking");
	}
	return (NULL);
}

void eating_time(t_philosopher *philo)
{
	t_data *data;

	data = philo->data;
	pthread_mutex_lock(&(data->forks[philo->left_fork]));
	printing_move(data, philo->id, "has taken a fork");
	pthread_mutex_lock(&(data->forks[philo->right_fork]));
	printing_move(data, philo->id, "has taken a fork");
	pthread_mutex_lock(&(data->moves_check));
	printing_move(data, philo->id, GREEN "is eating" RESET);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&(data->moves_check));
	ft_usleep(data->time_to_eat, data);
	philo->times_ate++;
	pthread_mutex_unlock(&(data->forks[philo->left_fork]));
	pthread_mutex_unlock(&(data->forks[philo->right_fork]));
}

void printing_move(t_data *data, int philo_id, char *string)
{
	pthread_mutex_lock(&(data->printing));
	if (!(data->flag_dead))
	{
		printf("%lli %d %s\n", get_time() - data->first_timestamp, philo_id, string);
	}
	pthread_mutex_unlock(&(data->printing));

}

void	check_for_deads(t_data *data,t_philosopher *philo)
{
	int i;

	while(data->flag_all_ate == 0)
	{
		i = 0;
		while (i < data->number_of_philo && data->flag_dead == 0)
		{
			pthread_mutex_lock(&(data->moves_check));
			if (time_diff(philo[i].last_meal_time, get_time()) > data->time_to_die)
			{
				printing_move(data, i, "died");
				data->flag_dead = 1;
			}
			pthread_mutex_unlock(&(data->moves_check));
			i++;
			usleep(100);
		}
		if (data->flag_dead == 1)
			break ;
		i = 0;
		while (data->times_to_eat != -1
			&& i < data->number_of_philo && philo[i].times_ate >= data->times_to_eat)
			i++;
		if (i == data->number_of_philo)
			data->flag_all_ate = 1;
		usleep(100);
	}
}


void finish_program(t_data *data, t_philosopher *philo)
{
	int i;
	
	i = 0;
	while (i < data->number_of_philo)
    {
        pthread_join(philo[i].thread_id, NULL);
		pthread_mutex_destroy(&(data->forks[i]));
		i++;
    }
	pthread_mutex_destroy((&data->printing));
	pthread_mutex_destroy((&data->moves_check));
	free(data->philosophers);
	free(data->forks);
}
