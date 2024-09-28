#include <unistd.h>
#include <stdarg.h>

void	put_str(char *str, int *len)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		write(2, "(null)", 6);
		*len += 6;
		return ;
	}
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		(*len)++;
		i++;
	}

}

void	put_nbr(int nbr, int *len)
{
	long nb;
	long mod;

	nb = nbr;
	if (nb < 0)
	{
		write(1, '-', 1);
		(*len)++;
		nb = -nb;
	}
	if (nb > 9)
		put_nbr((nb / 10), len);
	mod = nb % 10 + '0';
	write(1, &mod, 1);
	(*len)++;
}

void	put_hex(int nbr, int *len)
{
	long nb;
	long mod;
	char *base = "0123456789abcdef";

	nb = (long) nbr;
	if (nb >= 16)
		put_hex((nb / 16), len);
	mod = nb % 16;
	write(1, &base[mod], 1);
	(*len)++;
}

static void	check_launc(va_list first,char *str, int  i, int *len)
{
	if (str[i] == 'd')
		put_nbr(va_arg(first, int),len);
	else if (str[i] == 'x')
		put_hex(va_arg(first, int),len);
	else if (str[i] == 's')
		put_str(va_arg(first, char *), len);
}

int	printf(char *str, ...)
{
	int i;
	int len;
	va_list first;

	i = 0;
	len = 0;
	if (str == 0)
		return (-1);
	va_start(first, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			i++;
			check_launc(first, str, i, &len);
		}
		else 
		{
			write(1, &str[i], 1);
			len++;
		}
		i++;
	}
	va_end(first);
	return (len);
}