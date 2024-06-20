/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 17:00:45 by eperperi          #+#    #+#             */
/*   Updated: 2024/06/20 16:57:24 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	sign;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '+')
			i++;
		else
		{
			sign = -1;
			i++;
		}
	}
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return (result * sign);
}

long long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long long	time_diff(long long prev, long long now)
{
	return (now - prev);
}

void	ft_usleep(long long time, t_data *data)
{
	long long	start_time;

	start_time = get_time();
	while (1)
	{
		pthread_mutex_lock(&(data->flag_dead_mutex));
		if (data->flag_dead)
		{
			pthread_mutex_unlock(&(data->flag_dead_mutex));
			break ;
		}
		pthread_mutex_unlock(&(data->flag_dead_mutex));
		if (time_diff(start_time, get_time()) >= time)
			break ;
		usleep(50);
	}
}

void	printing_move(t_data *data, int philo_id, char *string)
{
	pthread_mutex_lock(&(data->printing));
	pthread_mutex_lock(&(data->flag_dead_mutex));
	if (!(data->flag_dead))
	{
		printf(LIGHT_YELLOW "%lli " RESET "%d %s\n",
			get_time() - data->first_timestamp, philo_id, string);
	}
	pthread_mutex_unlock(&(data->flag_dead_mutex));
	pthread_mutex_unlock(&(data->printing));
}
