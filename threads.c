/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:49:54 by eperperi          #+#    #+#             */
/*   Updated: 2024/06/11 13:45:33 by eperperi         ###   ########.fr       */
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
	   for (i = 0; i < data->number_of_philo; i++)
    {
        if (pthread_join(philo[i].thread_id, NULL) != 0)
        {
            printf("Failed to join thread %d\n", i);
            return (1);
        }
    }
	return (0);
}

void *routine(void *temp_philo)
{
	t_philosopher *philo;
	t_data *data;
	pthread_mutex_t mutex;
	
	if (pthread_mutex_init(&mutex, NULL) != 0)
	{
		printf("Failed to initialize mutex\n");
		return (NULL);
	}

	philo = (t_philosopher *)temp_philo;
	data = philo->data;
	pthread_mutex_lock(&mutex);
	int a = 0;
	for (int i = 0; i < 3; i++)
	{
		a += 1;
		printf("x + 1 : %d\n", a);
	}
	pthread_mutex_unlock(&mutex);
	
	return (NULL);
}