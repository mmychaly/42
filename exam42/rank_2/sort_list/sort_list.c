#include "list.h"
#include <stdlib.h>

t_list	*sort_list(t_list* lst, int (*cmp)(int, int))
{
		int temp;
		t_list *start;

		start = lst;
		while (lst->next != NULL)
		{
			if (cmp (lst->data, lst->next->data) == 0)
			{
				temp = lst->data;
				lst->data = lst->next->data;
				lst->next->data = temp;
				lst = start; //СТрочка кода нужна для того что бы после смещения начинать проверку заново,так как если просто переходить к следуюшийм элементам то предыдущий может оказаться больше нынешнего но мы это уже не проверям
			}
			else
				lst =lst->next;
		}
		return (start);
}