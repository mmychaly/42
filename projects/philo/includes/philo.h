/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 10:52:33 by mmychaly          #+#    #+#             */
/*   Updated: 2024/12/27 04:42:53 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	int					last_meal;
	int					eating;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					failed_attempts;
	int					nb_phil;
	int					num_eat;
	int					*start_time;
	int					*dead;
	int					*l_flag;
	int					*r_flag;

	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*general_mutex;
	pthread_mutex_t		*dead_mutex;
	pthread_mutex_t		*print_mutex;
	pthread_mutex_t		*meal_mutex;
}	t_philo;

typedef struct s_data
{
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_phil;
	int					num_eat;
	int					flag_dead;
	int					start_time;
	int					*forks_flag;

	t_philo				*philos;
	pthread_mutex_t		mutex;
	pthread_mutex_t		dead_mutex;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		meal_mutex;
	pthread_mutex_t		*forks;
}						t_data;

int		ft_atoi(const char *nptr);
int		check_digit(int i);
int		chek_args(int argc, char **args);
void	init_phelsophers(t_data *data);
int		init_mutex(t_data *data);
int		init_data(t_data *data, int argc, char **args);
void	*launch_routine(void *arg);
int		lock_forks(t_philo *philo);
int		lock_first_fork(t_philo *philo);
int		lock_seconde_fork(t_philo *philo);
void	philosopher_eat(t_philo *philo);
void	philosopher_sleep(t_philo *philo);
void	philosopher_think(t_philo *philo);
void	*monitoring_philosophers(void *arg);
int		check_dead(t_philo *philo);
void	print_message(char *str, t_philo *philo);
void	print_fork_message(char *str, int time, t_philo *philo);
void	sleep_time(int time, t_philo *philo);
int		get_time(void);
void	free_all(t_data *data);
void	unlock_mutex(t_philo *philo);
int		handling_mutex(t_data *data, int i);
int		calculate_delay(t_philo *philo);
#endif
