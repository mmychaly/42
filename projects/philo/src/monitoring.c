/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 01:38:32 by mmychaly          #+#    #+#             */
/*   Updated: 2024/12/27 04:41:13 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	calculate_delay(t_philo *philo)
{
	int		base_delay;
	int		time_since_meal;
	float	urgency_factor;

	base_delay = 30;
	urgency_factor = 1.0;
	pthread_mutex_lock(philo->meal_mutex);
	time_since_meal = get_time() - philo->last_meal;
	pthread_mutex_unlock(philo->meal_mutex);
	if (time_since_meal > (philo->time_to_die * 0.8))
		urgency_factor = 0.1;
	else if (time_since_meal > (philo->time_to_die * 0.5))
		urgency_factor = 0.3;
	if (philo->nb_phil > 100)
		base_delay = 40;
	else if (philo->nb_phil > 50)
		base_delay = 35;
	if (philo->failed_attempts > 30)
		return (10);
	if (philo->failed_attempts > 15)
		urgency_factor *= 0.3;
	else if (philo->failed_attempts > 10)
		urgency_factor *= 0.5;
	return ((int)(base_delay * urgency_factor));
}

int	check_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_mutex);
	if (*(philo->dead) == 1)
	{
		pthread_mutex_unlock(philo->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_mutex);
	return (0);
}

int	handling_mutex(t_data *data, int i)
{
	pthread_mutex_lock(&data->meal_mutex);
	if (data->num_eat == data->philos[0].eating)
	{
		pthread_mutex_unlock(&data->meal_mutex);
		return (0);
	}
	if (get_time() - data->philos[i].last_meal > data->time_to_die)
	{
		pthread_mutex_unlock(&data->meal_mutex);
		pthread_mutex_lock(&data->print_mutex);
		pthread_mutex_lock(&data->dead_mutex);
		data->flag_dead = 1;
		pthread_mutex_unlock(&data->dead_mutex);
		printf("%i %i died\n", get_time() - data->start_time,
			data->philos[i].id);
		pthread_mutex_unlock(&data->print_mutex);
		return (0);
	}
	pthread_mutex_unlock(&data->meal_mutex);
	return (1);
}

void	*monitoring_philosophers(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *) arg;
	while (1)
	{
		i = 0;
		while (i < data->nb_phil)
		{
			if (handling_mutex(data, i) == 0)
				return (0);
			i++;
		}
		usleep(50);
	}
	return (0);
}
