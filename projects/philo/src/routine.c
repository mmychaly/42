/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 02:31:22 by mmychaly          #+#    #+#             */
/*   Updated: 2024/12/27 22:50:44 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	lock_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
		return (lock_first_fork(philo));
	else
		return (lock_seconde_fork(philo));
	return (0);
}

void	philosopher_eat(t_philo *philo)
{
	print_message("is eating", philo);
	pthread_mutex_lock(philo->meal_mutex);
	philo->last_meal = get_time();
	philo->eating += 1;
	pthread_mutex_unlock(philo->meal_mutex);
	sleep_time(philo->time_to_eat, philo);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_lock(philo->general_mutex);
	*(philo->l_flag) = 0;
	*(philo->r_flag) = 0;
	pthread_mutex_unlock(philo->general_mutex);
}

void	philosopher_sleep(t_philo *philo)
{
	print_message("is sleeping", philo);
	sleep_time(philo->time_to_sleep, philo);
}

void	philosopher_think(t_philo *philo)
{
	int	multiplier;

	if (philo->nb_phil > 30)
		multiplier = 10;
	else
		multiplier = 2;
	print_message("is thinking", philo);
	usleep((philo->time_to_eat / 4) * (philo->nb_phil * multiplier));
}

void	*launch_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->nb_phil == 1)
		return (0);
	if (philo->id % 2 == 0)
		usleep((philo->time_to_eat / 4) * philo->nb_phil);
	while (1)
	{
		if (check_dead(philo) == 1)
			return (0);
		pthread_mutex_lock(philo->meal_mutex);
		if (philo->eating == philo->num_eat)
			return (pthread_mutex_unlock(philo->meal_mutex), NULL);
		pthread_mutex_unlock(philo->meal_mutex);
		if (lock_forks(philo) == 0)
		{
			if (check_dead(philo))
				return (unlock_mutex(philo), NULL);
			philosopher_eat(philo);
//			if (check_dead(philo) == 1)
//				return (0);
			philosopher_sleep(philo);
//			if (check_dead(philo) == 1)
//				return (0);
			philosopher_think(philo);
		}
	}
	return (0);
}
