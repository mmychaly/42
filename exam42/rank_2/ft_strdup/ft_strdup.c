
#include "stdlib.h"
#include "stdio.h"

char    *ft_strdup(char *src)
{
	int i;
	int len;
	char *dup;

	i = 0;
	len = 0;
	while(src[len] != '\0')
		len++;
	dup = malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (NULL);
	while (src[i] != '\0')
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int main (void)
{
	char *str;

	str = ft_strdup("salut");
	printf("%s\n", str);
	return (0);
}