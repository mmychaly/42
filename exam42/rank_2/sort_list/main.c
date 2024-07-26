#include "list.h"
#include <stdlib.h>
#include <stdio.h>


t_list *ft_creat_new(int data)
{
	t_list *new;

	new = malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->data = data;
	new->next = NULL;
	return (new);
}

int ascending(int a, int b)
{
	return (a <= b);
}

int main(void)
{
	t_list *begine;
	
	begine = ft_creat_new(1);
	begine->next = ft_creat_new(0);
	begine->next->next = ft_creat_new(10);
	begine->next->next->next = ft_creat_new(5);

	begine = sort_list(begine, ascending);

	while (begine->next != NULL)
	{
		printf("%i\n", begine->data);
		begine = begine->next;
	}
	printf("%i\n", begine->data);
	return (0);
}