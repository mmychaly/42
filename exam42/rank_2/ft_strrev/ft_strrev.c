
#include <stdio.h> 

char    *ft_strrev(char *str)
{
	int i;
	int len;
	char temp;

	i = 0;
	len = 0;
	while (str[len] != '\0')
		len++;
	while (len > i)
	{
		temp = str[i];
		str[i] = str[len - 1];
		str[len - 1] = temp;
		i++;
		len--;
	}
	return (str);
}

int main(void)
{
	char str[5] = "Mich";
	char *new;

	new = ft_strrev(str);
	printf("new %s\n", new);
	printf("str %s\n", str);
	return (0);
}