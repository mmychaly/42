#ifndef PHILO_H
#define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				last_meal;
	int				eating; //Нужен?
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_eat;
	int				*start_time;
	int				*dead;

	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*general_mutex;
}	t_philo;

typedef struct s_data
{
	
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					num_of_philos;
	int					num_eat;
	int					flag_dead;
	int					start_time;

	t_philo				*philos;
	pthread_mutex_t		mutex;
	pthread_mutex_t		*forks;
	
}						t_data;

int	ft_atoi(const char *nptr);
int	check_digit(int i);


int	chek_args(int argc, char **args);
int	init_phelsophers(t_data *data);
int	init_mutex(t_data *data);
int	init_data(t_data *data, int argc, char **args);

void	*launch_routine(void *arg);
int		lock_forks(t_philo *philo);
void	philosopher_eat(t_philo *philo);
void	philosopher_sleep(t_philo *philo);
void	philosopher_think(t_philo *philo);

void	*monitoring_philosophers(void *arg);
int check_dead(t_philo *philo);

void	print_message(char *str, t_philo *philo);
void	sleep_time(int time, t_philo *philo);
int		get_time(void);
void	free_all(t_data *data);
#endif