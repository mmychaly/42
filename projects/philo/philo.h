#ifndef PHILO_H
#define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				last_meal;

}	t_philo;

typedef struct s_data
{
	int					dead;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					num_of_philos;
	int					num_times_to_eat;
	int					start_time;		
	t_philo				*philos;
	pthread_mutex_t		mutex;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
}						t_data;
#endif