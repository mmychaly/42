#include "philo.h"

int	chek_args(int argc, char **args)
{
	int	i;
	int	i_2;

	i = 0;
	i_2 = 0;
	if (argc != 5 | argc != 6)
	{
		write(2, "Error: wrong number of arguments\n", 33);
		return (1);
	}
	while (args[i] != NULL)
	{
		i_2 = 0;
		if (args[i][0] == "+")
			i_2++;
		while (args[i][i_2] != '\0')
		{
			if (check_digit(args[i][i_2]) == 0)
			{
				printf("Error: wrong agrument (%s)\n", args[i]);
				return (1);
			}
			i_2++;
		}
		if (ft_atoi(args[i]) <= 0)
		{
			printf("Error: wrong agrument (%s)\n", args[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

void	init_data(t_data *data)
{

}

int	main(int argc, char *args[])
{
	t_data data;

	if (chek_args(argc, args) == 1)
		return (1);
	init_data(&data);
}