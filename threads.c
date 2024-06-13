/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:49:54 by eperperi          #+#    #+#             */
/*   Updated: 2024/06/13 15:34:46 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *temp_philo);
void	eating_time(t_philosopher *philo);
void	finish_program(t_data *data, t_philosopher *philo);
void	check_for_deads(t_data *data, t_philosopher *philo);

int	threads(t_data *data)
{
	int				i;
	t_philosopher	*philo;

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

void	*routine(void *temp_philo)
{
	t_philosopher	*philo;
	t_data			*data;

	philo = (t_philosopher *)temp_philo;
	data = philo->data;
	if (philo->id % 2)
		usleep(15000);
	while (data->flag_dead == 0)
	{
		eating_time(philo);
		if (data->flag_all_ate)
			break ;
		printing_move(data, philo->id, YELLOW "is sleeping" RESET);
		ft_usleep(data->time_to_sleep, data);
		printing_move(data, philo->id, CYAN "is thinking" RESET);
	}
	return (NULL);
}

void	eating_time(t_philosopher *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&(data->forks[philo->left_fork]));
	printing_move(data, philo->id, MAGENTA "has taken a fork" RESET);
	pthread_mutex_lock(&(data->forks[philo->right_fork]));
	printing_move(data, philo->id, MAGENTA "has taken a fork" RESET);
	pthread_mutex_lock(&(data->moves_check));
	printing_move(data, philo->id, BOLD GREEN "is eating" RESET);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&(data->moves_check));
	ft_usleep(data->time_to_eat, data);
	philo->times_ate++;
	pthread_mutex_unlock(&(data->forks[philo->left_fork]));
	pthread_mutex_unlock(&(data->forks[philo->right_fork]));
}

void	check_for_deads(t_data *d, t_philosopher *p)
{
	int	i;

	while (d->flag_all_ate == 0)
	{
		i = -1;
		while (++i < d->number_of_philo && d->flag_dead == 0)
		{
			pthread_mutex_lock(&(d->moves_check));
			if (time_diff(p[i].last_meal_time, get_time()) > d->time_to_die)
			{
				printing_move(d, i, UNDERLINE BOLD RED "DIED" RESET);
				pthread_mutex_lock(&(d->flag_dead_mutex));
				d->flag_dead = 1;
				pthread_mutex_unlock(&(d->flag_dead_mutex));
			}
			usleep(100);
			pthread_mutex_unlock(&(d->moves_check));
		}
		if (d->flag_dead == 1)
			break ;
		i = 0;
		while (d->times_to_eat != -1
			&& i < d->number_of_philo && p[i].times_ate >= d->times_to_eat)
			i++;
		if (i == d->number_of_philo)
			d->flag_all_ate = 1;
	}
}

void	finish_program(t_data *data, t_philosopher *philo)
{
	int	i;

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
