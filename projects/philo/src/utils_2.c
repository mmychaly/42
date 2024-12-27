/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 06:58:07 by mmychaly          #+#    #+#             */
/*   Updated: 2024/12/27 04:47:27 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	unlock_mutex(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	print_message(char *str, t_philo *philo)
{
	if (check_dead(philo) != 1)
	{
		pthread_mutex_lock(philo->print_mutex);
		printf("%i %i %s\n", get_time() - *(philo->start_time), philo->id, str);
		pthread_mutex_unlock(philo->print_mutex);
	}
}

void	print_fork_message(char *str, int time, t_philo *philo)
{
	pthread_mutex_lock(philo->print_mutex);
	printf("%i %i %s\n", time - *(philo->start_time), philo->id, str);
	pthread_mutex_unlock(philo->print_mutex);
}

int	lock_first_fork(t_philo *philo)
{
	int	can_take_forks;

	can_take_forks = 0;
	pthread_mutex_lock(philo->general_mutex);
	if (*(philo->r_flag) == 0 && *(philo->l_flag) == 0)
	{
		*(philo->r_flag) = 1;
		*(philo->l_flag) = 1;
		can_take_forks = 1;
	}
	pthread_mutex_unlock(philo->general_mutex);
	if (can_take_forks == 1)
	{
		pthread_mutex_lock(philo->r_fork);
		pthread_mutex_lock(philo->l_fork);
		if (check_dead(philo) != 1)
		{
			print_fork_message("has taken a fork", get_time(), philo);
			print_fork_message("has taken a fork", get_time(), philo);
		}
		philo->failed_attempts = 0;
		return (0);
	}
	philo->failed_attempts++;
	return (usleep(calculate_delay(philo)), 1);
}

int	lock_seconde_fork(t_philo *philo)
{
	int	can_take_forks;

	can_take_forks = 0;
	pthread_mutex_lock(philo->general_mutex);
	if (*(philo->l_flag) == 0 && *(philo->r_flag) == 0)
	{
		*(philo->l_flag) = 1;
		*(philo->r_flag) = 1;
		can_take_forks = 1;
	}
	pthread_mutex_unlock(philo->general_mutex);
	if (can_take_forks == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		pthread_mutex_lock(philo->r_fork);
		if (check_dead(philo) != 1)
		{
			print_fork_message("has taken a fork", get_time(), philo);
			print_fork_message("has taken a fork", get_time(), philo);
		}
		philo->failed_attempts = 0;
		return (0);
	}
	philo->failed_attempts++;
	return (usleep(calculate_delay(philo)), 1);
}
