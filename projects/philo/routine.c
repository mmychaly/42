/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 02:31:22 by mmychaly          #+#    #+#             */
/*   Updated: 2024/12/18 06:21:49 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	lock_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		if (check_dead(philo) != 1)
			print_message("has taken a fork //philo->r_fork//1", philo);
	}	
	else
	{
		pthread_mutex_lock(philo->l_fork);
		if (check_dead(philo) != 1)
			print_message("has taken a fork //philo->l_fork//1", philo);
	}
	if (philo->id % 2 == 0)
	{
		if (pthread_mutex_lock(philo->l_fork) != 0)
		{
			pthread_mutex_unlock(philo->r_fork);
			print_message("pthread_mutex_unlock(philo->r_fork);", philo);
			return (1);
		}
		if (check_dead(philo) != 1)
			print_message("has taken a fork //philo->l_fork//2", philo);
	}
	else
	{
		if (pthread_mutex_lock(philo->r_fork) != 0)
		{
			pthread_mutex_unlock(philo->l_fork);
			print_message("pthread_mutex_unlock(philo->l_fork);", philo);
			return (1);
		}
		if (check_dead(philo) != 1)
			print_message("has taken a fork //philo->r_fork //2", philo);
	}
	return (0);
}

void	philosopher_eat(t_philo *philo)
{
	print_message("is eating", philo);
	pthread_mutex_lock(philo->general_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->general_mutex);
	sleep_time(philo->time_to_eat, philo);
	philo->eating += 1;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	philosopher_sleep(t_philo *philo)
{
	print_message("is sleeping", philo);
	sleep_time(philo->time_to_sleep, philo);
}

void	philosopher_think(t_philo *philo)
{
	print_message("is thinking", philo);
}

void	*launch_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo*) arg;
//	printf("launch_routine philo == %i //philo->last_meal == %i //*(philo->start_time) == %i\n", philo->id, philo->last_meal, *(philo->start_time));
	while (*(philo->dead) == 0 && philo->eating != philo->num_eat)
	{
//		printf("launch_routine in wh //philo == %i // eating == %i\n", philo->id, philo->eating);
		if (check_dead(philo) == 1)
			return (0);
		if (lock_forks(philo) == 0)
		{
			if (check_dead(philo) == 1)
			{
				pthread_mutex_unlock(philo->l_fork);
				pthread_mutex_unlock(philo->r_fork);
				return (0);
			}
			philosopher_eat(philo);
			if (check_dead(philo) == 1)
				return (0);
			philosopher_sleep(philo);
			if (check_dead(philo) == 1)
				return (0);
			philosopher_think(philo);
		}
	}
//	printf("fin //philo == %i // eating == %i\n", philo->id, philo->eating);
	return (0);
}
