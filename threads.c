/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:49:54 by eperperi          #+#    #+#             */
/*   Updated: 2024/06/11 13:28:33 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine(void *temp_philo);

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
		i++;
	}
	return (0);
}

void *routine(void *temp_philo)
{
	t_philosopher *philo;
	t_data *data;
	int a = 0;

	philo = (t_philosopher *)temp_philo;
	data = philo->data;
	for (int i = 0; i < 2; i++)
	{
		printf("x + 1 : %d\n", a + i);
	}
	
	return (NULL);
}