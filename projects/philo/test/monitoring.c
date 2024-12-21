/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 01:38:32 by mmychaly          #+#    #+#             */
/*   Updated: 2024/12/20 17:43:57 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->general_mutex);
	if(*(philo->dead) == 1)
	{
		pthread_mutex_unlock(philo->general_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->general_mutex);
	return (0);
}

void	*monitoring_philosophers(void *arg)
{
	t_data *data;
	int		i;

	i = 0;
	data = (t_data*) arg;
	while(1)
	{
//		printf("monitoring_philosophers\n");
		if (data->num_eat == data->philos[0].eating)
		{
//			printf("in monitiring data->num_eat == data->philos[0].eating\n");
			return (0);
		}
		while (i < data->num_of_philos)
		{
			pthread_mutex_lock(&data->mutex);
			if (get_time() - data->philos[i].last_meal > data->time_to_die)
			{
				data->flag_dead = 1;
				printf("%i %i died\n", get_time() - data->start_time, data->philos[i].id);
				pthread_mutex_unlock(&data->mutex);
				return (0);
			}
			pthread_mutex_unlock(&data->mutex);
			i++;
		}
		i = 0;
		usleep(50);
	}
	return (0);
}
