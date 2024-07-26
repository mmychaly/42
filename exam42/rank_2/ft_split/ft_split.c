
#include <stdlib.h>
#include <stdio.h>

char    **ft_split(char *str)
{
	int len;
	int i;
	int i_2;
	int word;
	char **strs;

	len = 0;
	i = 0;
	i_2 = 0;
	word = 0;
	while (str[len])
		len++;
	while (str[i] != '\0')
	{
		if ((str[i] >= 33 && str[i] <= 126) && (str[i + 1] == '\t' || str[i + 1] == ' ' || str[i + 1] == '\n' || str[i + 1] == '\0'))
			word++;
		i++;
	}
	strs = malloc (sizeof(char *) * (word + 1));
	if (strs == NULL)
		return (NULL);
	i = 0;
	strs[word] = NULL;
	while (i < word)
	{
		strs[i] = malloc(sizeof(char) * (len + 1));
		if (strs[i] == NULL)
			return (NULL);
		i++;
	}
	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 33 && str[i] <= 126)
		{
			strs[i_2][len] = str[i];
			printf("in 1 if %c\n", strs[i_2][len]);
			len++;
		}
		if ((str[i] >= 33 && str[i] <= 126) && (str[i + 1] == '\t' || str[i + 1] == ' ' || str[i + 1] == '\n' || str[i + 1] == '\0'))
		{
			printf("in 2 if\n");
			len++;
			strs[i_2][len] = '\0';
			len = 0;
			i_2++;
		}
		i++;
	}
	return (strs);
}

int main(void)
{
	char **strs;
	int i;

	i = 0;
	strs = ft_split("Salutcommentvastu?");
	while (strs[i] != NULL)
	{
		printf("strs[%i] == %s\n", i, strs[i]);
		i++;
	}
	return (0);
}