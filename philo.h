/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:47:41 by eperperi          #+#    #+#             */
/*   Updated: 2024/06/13 14:57:53 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

# define RESET "\033[0m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define MAGENTA "\033[35m"
# define CYAN "\x1b[36m"
# define RED "\033[31m"
# define LIGHT_YELLOW "\x1b[93m"
# define BOLD "\033[1m"
# define UNDERLINE "\033[4m"

typedef struct s_philosopher
{
	int				id;
	int				times_ate;
	int				left_fork;
	int				right_fork;
	long long		last_meal_time;
	struct s_data	*data;
	pthread_t		thread_id;

}	t_philosopher;

typedef struct s_data
{
	int				number_of_philo;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_to_eat;
	int				time_to_die;
	int				flag_dead;
	long long		first_timestamp;
	t_philosopher	*philosophers;
	pthread_mutex_t	*forks;
	pthread_mutex_t	moves_check;
	pthread_mutex_t	printing;
	int				flag_all_ate;
}	t_data;

int			ft_atoi(const char *str);
long long	get_time(void);
void		ft_usleep(long long time, t_data *data);
int			threads(t_data *data);
long long	time_diff(long long prev, long long now);
void		printing_move(t_data *data, int philo_id, char *string);

#endif