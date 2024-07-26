#include "unistd.h"

int	main(int argc, char **argv)
{
	int i;
	char symb;

	i = 0;
	if (argc == 2)
	{
		while (argv[1][i] != '\0')
		{
			if ((argv[1][i] >= 'a' && argv[1][i] <= 'm') || (argv[1][i] >= 'A' && argv[1][i] <= 'M'))
			{	
				symb = argv[1][i] + 13;
				write (1, &symb, 1);
			}
			else if ((argv[1][i] >= 'n' && argv[1][i] <= 'z') || (argv[1][i] >= 'N' && argv[1][i] <= 'Z'))
			{	
				symb = argv[1][i] - 13;
				write (1, &symb, 1);
			}
			else 
				write(1, &argv[1][i], 1);
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}