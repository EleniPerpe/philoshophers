/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:22:29 by eperperi          #+#    #+#             */
/*   Updated: 2024/06/25 13:24:58 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	keep_checking(t_data *d, t_philosopher *p);

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
			printing_move(d, i, UNDERLINE BOLD RED "PHILO DIED" RESET);
			pthread_mutex_lock(&(d->flag_dead_mutex));
			d->flag_dead = 1;
			pthread_mutex_unlock(&(d->flag_dead_mutex));
		}
		pthread_mutex_unlock(&(p->last_meal_mutex));
		pthread_mutex_unlock(&(d->moves_check));
		usleep(100);
	}
}
