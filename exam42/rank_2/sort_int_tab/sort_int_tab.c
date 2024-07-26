
#include <stdio.h>

void sort_int_tab(int *tab, unsigned int size)
{
	unsigned int i;
	unsigned int i_2;
	unsigned int temp;

	i = 0;

	while (i < size)
	{
		i_2 = i + 1;
		while (i_2 < size)
		{
			if (tab[i] > tab[i_2])
			{
				temp = tab[i];
				tab[i] = tab[i_2];
				tab[i_2] = temp;
			}
			i_2++;
		}
		i++;
	}
}

int main(void)
{
	int tab[6] = {1, 8, 2, 6, 1, 3};
	int i;

	i = 0;
	sort_int_tab(tab, 6);
	while (i < 6)
	{
		printf("%i\n", tab[i]);
		i++;
	}
	return (0);
}