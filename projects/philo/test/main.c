/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 02:30:49 by mmychaly          #+#    #+#             */
/*   Updated: 2024/12/18 01:24:42 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	launch_philosphers(t_data *data)
{
	int	i;
	pthread_t monitoring;
	i = 0;
	data->start_time = get_time();
	while(i < data->num_of_philos)
	{
		data->philos[i].last_meal = data->start_time;
		i++;
	}
	i = 0;
	while(i < data->num_of_philos)
	{
		pthread_create(&data->philos[i].thread, NULL, launch_routine, (void *)&data->philos[i]);
		i++;
	}
	pthread_create(&monitoring, NULL, monitoring_philosophers, (void *)data);
	i = 0;
	while(i < data->num_of_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitoring, NULL);
}

int	main(int argc, char *args[])
{
	t_data data;

	if (chek_args(argc, args) == 1)
		return (1);
	if (init_data(&data, argc, args) == 1)
		return (1);
	launch_philosphers(&data);
	free_all(&data);
	return (0);
}
