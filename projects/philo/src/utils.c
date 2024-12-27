/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 06:57:56 by mmychaly          #+#    #+#             */
/*   Updated: 2024/12/27 04:44:26 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(const char *nptr)
{
	int		i;
	int		negativ;
	long	result;

	i = 0;
	negativ = 1;
	result = 0;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			negativ *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = (result * 10) + (nptr[i] - '0');
		i++;
	}
	result = result * negativ;
	if (result < INT_MIN || result > INT_MAX)
		return (-1);
	return ((int)result);
}

int	check_digit(int i)
{
	if (i >= '0' && i <= '9')
		return (1);
	return (0);
}

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_phil)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->mutex);
	pthread_mutex_destroy(&data->dead_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	free(data->forks);
	free(data->forks_flag);
	free(data->philos);
}

int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	sleep_time(int time, t_philo *philo)
{
	int	start;

	start = get_time();
	while ((get_time() - start) < time)
	{
		if (check_dead(philo) == 1)
			return ;
		usleep(100);
	}
}
