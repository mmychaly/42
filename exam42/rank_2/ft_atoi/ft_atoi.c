
#include <stdlib.h>
#include <stdio.h>

int	ft_atoi(const char *str)
{
	int i;
	long nbr;
	long signe;

	i = 0;
	nbr = 0;
	signe = 1;

	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = -1;
		i++;
	}
	while ((str[i] >= 48 && str[i] <= 57))
	{
		nbr = (nbr * 10) + (str[i] - 48);
		i++;
	}
	return (nbr * signe);
}


int main(void)
{
	printf("ft_atoi %i\n", ft_atoi(" -10r0"));
	printf("atoi %i\n", atoi(" -10r0"));
	return (0);
}