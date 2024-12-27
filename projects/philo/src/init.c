/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 02:29:10 by mmychaly          #+#    #+#             */
/*   Updated: 2024/12/27 04:42:44 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	chek_args(int argc, char **args)
{
	int	i;
	int	i_2;

	i = 1;
	i_2 = 0;
	if (argc != 5 && argc != 6)
		return (write(2, "Error: wrong number of arguments \n", 35), 1);
	while (args[i] != NULL)
	{
		i_2 = 0;
		if (args[i][0] == '+' || args[i][0] == '-')
			i_2++;
		while (args[i][i_2] != '\0')
		{
			if (check_digit(args[i][i_2]) == 0)
				return (printf("Error: wrong agrument is not digit (%s)\n",
						args[i]), 1);
			i_2++;
		}
		if (ft_atoi(args[i]) <= 0)
			return (printf("Error: wrong agrument (%s)\n", args[i]), 1);
		i++;
	}
	return (0);
}

void	init_phelsophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_phil)
	{
		memset(&data->philos[i], 0, sizeof(t_philo));
		data->philos[i].id = i + 1;
		data->philos[i].time_to_die = data->time_to_die;
		data->philos[i].time_to_eat = data->time_to_eat;
		data->philos[i].time_to_sleep = data->time_to_sleep;
		data->philos[i].num_eat = data->num_eat;
		data->philos[i].dead = &data->flag_dead;
		data->philos[i].start_time = &data->start_time;
		data->philos[i].last_meal = data->start_time;
		data->philos[i].nb_phil = data->nb_phil;
		data->philos[i].general_mutex = &data->mutex;
		data->philos[i].dead_mutex = &data->dead_mutex;
		data->philos[i].meal_mutex = &data->meal_mutex;
		data->philos[i].print_mutex = &data->print_mutex;
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].l_flag = &data->forks_flag[i];
		data->philos[i].r_fork = &data->forks[(i + 1) % data->nb_phil];
		data->philos[i].r_flag = &data->forks_flag[(i + 1) % data->nb_phil];
		i++;
	}
}

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_phil);
	if (data->forks == NULL)
		return (1);
	data->forks_flag = malloc(sizeof(int) * data->nb_phil);
	if (data->forks_flag == NULL)
		return (1);
	data->philos = malloc (sizeof(t_philo) * data->nb_phil);
	if (data->philos == NULL)
		return (1);
	while (i < data->nb_phil)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		data->forks_flag[i] = 0;
		i++;
	}
	pthread_mutex_init(&data->mutex, NULL);
	pthread_mutex_init(&data->meal_mutex, NULL);
	pthread_mutex_init(&data->dead_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	return (0);
}

int	init_data(t_data *data, int argc, char **args)
{
	data->nb_phil = ft_atoi(args[1]);
	data->time_to_die = ft_atoi(args[2]);
	data->time_to_eat = ft_atoi(args[3]);
	data->time_to_sleep = ft_atoi(args[4]);
	if (argc == 6)
		data->num_eat = ft_atoi(args[5]);
	else
		data->num_eat = -1;
	data->flag_dead = 0;
	data->start_time = get_time();
	if (init_mutex(data) == 1)
		return (1);
	init_phelsophers(data);
	return (0);
}
