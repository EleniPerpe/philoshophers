/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:49:54 by eperperi          #+#    #+#             */
/*   Updated: 2024/06/20 15:36:18 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *temp_philo);
void	eating_time(t_philosopher *philo);
void	finish_program(t_data *data, t_philosopher *philo);
void	check_for_deads(t_data *data, t_philosopher *philo);
void	keep_checking(t_data *d, t_philosopher *p);
int		break_check(t_data *data, t_philosopher *philo);

int	threads(t_data *data)
{
	int				i;
	t_philosopher	*philo;

	i = 0;
	philo = data->philosophers;
	data->first_timestamp = get_time();
	while (i < data->number_of_philo)
	{
		if (pthread_create(&(philo[i].thread_id), NULL, routine, &(philo[i])))
			return (3);
		pthread_mutex_lock(&(philo[i].last_meal_mutex));
		philo[i].last_meal_time = get_time();
		pthread_mutex_unlock(&(philo[i].last_meal_mutex));
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
	{
		printing_move(data, philo->id, CYAN "is thinking" RESET);
		usleep(15000);
	}
	while (1)
	{
		if (break_check(data, philo) != 0)
			break ;
		pthread_mutex_unlock(&(data->flag_ate_mutex));
		printing_move(data, philo->id, YELLOW "is sleeping" RESET);
		ft_usleep(data->time_to_sleep, data);
		printing_move(data, philo->id, CYAN "is thinking" RESET);
	}
	return (NULL);
}

int	break_check(t_data *data, t_philosopher *philo)
{
	pthread_mutex_lock(&(data->flag_dead_mutex));
	if (data->flag_dead != 0)
	{
		pthread_mutex_unlock(&(data->flag_dead_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(data->flag_dead_mutex));
	eating_time(philo);
	pthread_mutex_lock(&(data->flag_ate_mutex));
	if (data->flag_all_ate)
	{
		pthread_mutex_unlock(&(data->flag_ate_mutex));
		return (1);
	}
	return (0);
}

void	eating_time(t_philosopher *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&(data->forks[philo->right_fork]));
	printing_move(data, philo->id, MAGENTA "has taken a fork" RESET);
	pthread_mutex_lock(&(data->forks[philo->left_fork]));
	printing_move(data, philo->id, MAGENTA "has taken a fork" RESET);
	pthread_mutex_lock(&(data->moves_check));
	pthread_mutex_lock(&(philo->last_meal_mutex));
	printing_move(data, philo->id, BOLD GREEN "is eating" RESET);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&(philo->last_meal_mutex));
	pthread_mutex_unlock(&(data->moves_check));
	ft_usleep(data->time_to_eat, data);
	pthread_mutex_lock(&(data->times_ate_mutex));
	philo->times_ate++;
	pthread_mutex_unlock(&(data->times_ate_mutex));
	pthread_mutex_unlock(&(data->forks[philo->left_fork]));
	pthread_mutex_unlock(&(data->forks[philo->right_fork]));
}

void	check_for_deads(t_data *d, t_philosopher *p)
{
	int	i;

	while (1)
	{
		i = 0;
		pthread_mutex_lock(&(d->flag_ate_mutex));
		if (d->flag_all_ate != 0)
		{
			pthread_mutex_unlock(&(d->flag_ate_mutex));
			break ;
		}
		pthread_mutex_unlock(&(d->flag_ate_mutex));
		while (d->times_to_eat != -1
			&& i < d->number_of_philo && p[i].times_ate >= d->times_to_eat)
			i++;
		if (i == d->number_of_philo)
		{
			pthread_mutex_lock(&(d->flag_ate_mutex));
			d->flag_all_ate = 1;
			pthread_mutex_unlock(&(d->flag_ate_mutex));
		}
		keep_checking(d, p);
		if (d->flag_dead == 1)
			break ;
	}
}

void	keep_checking(t_data *d, t_philosopher *p)
{
	int	i;

	i = -1;
	while (++i < d->number_of_philo)
	{
		pthread_mutex_lock(&(d->flag_dead_mutex));
		if (d->flag_dead != 0)
		{
			pthread_mutex_unlock(&(d->flag_dead_mutex));
			break ;
		}
		pthread_mutex_unlock(&(d->flag_dead_mutex));
		pthread_mutex_lock(&(d->moves_check));
		pthread_mutex_lock(&(p->last_meal_mutex));
		if (time_diff(p[i].last_meal_time, get_time()) > d->time_to_die)
		{
			printing_move(d, i, UNDERLINE BOLD RED "ALL DIED" RESET);
			pthread_mutex_lock(&(d->flag_dead_mutex));
			d->flag_dead = 1;
			pthread_mutex_unlock(&(d->flag_dead_mutex));
		}
		pthread_mutex_unlock(&(p->last_meal_mutex));
		pthread_mutex_unlock(&(d->moves_check));
		usleep(100);
	}
}

void	finish_program(t_data *data, t_philosopher *philo)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_join(philo[i].thread_id, NULL);
		i++;
	}
	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_mutex_destroy(&(data->forks[i]));
		pthread_mutex_destroy(&philo[i].last_meal_mutex);
		i++;
	}
	pthread_mutex_destroy((&data->printing));
	pthread_mutex_destroy((&data->moves_check));
	pthread_mutex_destroy((&data->flag_dead_mutex));
	free(data->philosophers);
	free(data->forks);
}
