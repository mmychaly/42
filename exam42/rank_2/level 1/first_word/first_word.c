#include <unistd.h>

void ft_display_word(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != 32 && str[i] != 9)
		{
			while (str[i] != '\0' && str[i] != 32 && str[i] != 9)
			{
				write(1, &str[i], 1);
				i++;
			}
			return ;
		}
		i++;
	}
}

int main(int argc, char **argv)
{
	if (argc == 2)
		ft_display_word(argv[1]);
	write(1, "\n", 1);
	return (0);
}