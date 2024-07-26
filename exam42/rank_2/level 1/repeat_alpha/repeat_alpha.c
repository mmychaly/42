#include <unistd.h>

void ft_repeat_alpha(char *str)
{
	int	i;
	int rep;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 'a' && str[i] <= 'z')
		{
			rep = str[i] - 96;
			while (rep != 0)
			{
				write(1, &str[i], 1);
				rep--;
			}
		}
		else if (str[i] >= 'A' && str[i] <= 'Z')
		{
			rep = str[i] - 64;
			while (rep != 0)
			{
				write(1, &str[i], 1);
				rep--;
			}
		}
		else 
			write(1, &str[i], 1);
		i++;
	}
}

int main(int argc, char **argv)
{
	if (argc == 2)
		ft_repeat_alpha(argv[1]);
	write(1, "\n", 1);
	return 0;
}