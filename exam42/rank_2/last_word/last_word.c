#include <unistd.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	int i;

	i = 0;
	if (argc == 2)
	{
		while (argv[1][i] != '\0')
			i++;
		while ( i > 0 )
		{
			if ((argv[1][i] > 33 && argv[1][i] < 126) && (argv[1][i-1] == 32 || argv[1][i-1] == 9))
				break ;
			i--;
		}
		while ((argv[1][i] >= 33 && argv[1][i] <= 126) && argv[1][i] != '\0' )
		{
			write(1, &argv[1][i], 1);
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}