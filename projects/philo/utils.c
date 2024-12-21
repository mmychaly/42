/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 06:57:56 by mmychaly          #+#    #+#             */
/*   Updated: 2024/12/21 08:30:56 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	return ((int)result * negativ);
}

int	check_digit(int i)
{
	if (i >= '0' && i <= '9')
		return (1);
	return (0);
}

void	free_all(t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->mutex);
	free(data->forks);
	free(data->forks_flag);
	free(data->philos);
}

int get_time(void)
{
	struct timeval time;

    gettimeofday(&time, NULL);
	return((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	sleep_time(int time, t_philo *philo)
{	
	int	start;

	start = get_time();
	while ((get_time() - start ) < time)
	{
		if (check_dead(philo) == 1)
			return ;
		usleep(100);
	}
}


void	print_message(char *str, t_philo *philo)
{
		if (check_dead(philo) != 1)
		{
			pthread_mutex_lock(philo->general_mutex);
			printf("%i %i %s\n",get_time() - *(philo->start_time), philo->id, str);
			pthread_mutex_unlock(philo->general_mutex);
		}
}

void	print_fork_message(char *str, int time, t_philo *philo)
{
	if (check_dead(philo) != 1)
	{
		pthread_mutex_lock(philo->general_mutex);
		printf("%i %i %s\n",time - *(philo->start_time), philo->id, str);
		pthread_mutex_unlock(philo->general_mutex);
	}
}
