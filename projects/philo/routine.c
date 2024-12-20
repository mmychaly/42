/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 02:31:22 by mmychaly          #+#    #+#             */
/*   Updated: 2024/12/21 08:32:28 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//int lock_seconde_fork(t_philo *philo)

int	lock_forks(t_philo *philo)
{
	int time_l_fork;
	int time_r_fork;

	time_l_fork = 0;
	time_r_fork = 0;
	if (philo->id % 2 == 0)
	{
		if (*(philo->r_flag) == 0)
		{
			pthread_mutex_lock(philo->r_fork);
			*(philo->r_flag) = 1;
			time_r_fork = get_time();
		}
	}	
	else
	{
		if (*(philo->l_flag) == 0)
		{
			pthread_mutex_lock(philo->l_fork);
			*(philo->l_flag) = 1;
			time_l_fork = get_time();
		}
	}
	if (philo->id % 2 == 0)
	{
		if (*(philo->l_flag) == 0 )
		{
			pthread_mutex_lock(philo->l_fork);
			*(philo->l_flag) = 1;
			time_l_fork = get_time();
		}
		else
		{
			pthread_mutex_unlock(philo->r_fork);
			*(philo->r_flag) = 0;
			time_r_fork = 0;
			return (1);
		}
		if (check_dead(philo) != 1)
		{
//			if (time_r_fork < 0)
			printf("time_r_fork == %i id %i\n", time_r_fork, philo->id);
			if (time_r_fork == 0)
				time_r_fork = get_time();
			print_fork_message("has taken a fork\n", time_r_fork, philo);
//			if (time_l_fork < 0)
			printf("time_l_fork == %i id %i\n", time_l_fork, philo->id);
			print_fork_message("has taken a fork\n", time_l_fork, philo);
		}	
	}
	else
	{
		if (*(philo->r_flag) == 0)
		{
			pthread_mutex_lock(philo->r_fork);
			*(philo->r_flag) = 1;
			time_r_fork = get_time();
		}
		else
		{
			pthread_mutex_unlock(philo->l_fork);
			*(philo->l_flag)  = 0;
			time_l_fork = 0;
			return (1);
		}
		if (check_dead(philo) != 1)
		{
//			if (time_l_fork < 0)
			printf("time_l_fork == %i id %i\n", time_l_fork, philo->id);
			if (time_l_fork == 0)
				time_l_fork = get_time() ;
			print_fork_message("has taken a fork\n",time_l_fork, philo);
//			if (time_r_fork < 0)
			printf("time_r_fork == %i id %i\n", time_r_fork, philo->id);
			print_fork_message("has taken a fork\n",time_r_fork, philo);
		}
	}
	time_l_fork = 0;
	time_r_fork = 0;
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
	*(philo->l_flag) = 0;
	pthread_mutex_unlock(philo->r_fork);
	*(philo->r_flag) = 0;
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
	while (*(philo->dead) == 0 && philo->eating != philo->num_eat)
	{
		if (check_dead(philo) == 1)
			return (0);
		if (lock_forks(philo) == 0)
		{
			if (check_dead(philo) == 1)
				return (unlock_mutex(philo), NULL);
			philosopher_eat(philo);
			if (check_dead(philo) == 1)
				return (0);
			philosopher_sleep(philo);
			if (check_dead(philo) == 1)
				return (0);
			philosopher_think(philo);
		}
		else 
			usleep(1000);
	}
	return (0);
}
