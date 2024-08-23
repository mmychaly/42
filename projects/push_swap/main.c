/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 23:22:04 by mmychaly          #+#    #+#             */
/*   Updated: 2024/08/23 17:28:21 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int main(int argc, char *argv[])
{
	t_stack *stack_a;
	
	if (argc > 1)
	{
		ft_init(&stack_a, argc, argv);
		ft_lstclear_mod(&stack_a);
	}
	return (0);

}


/*
	t_stack *stack_a;
	t_stack *stack_a_print;
	int i;
	
	i = 0;
	if (argc > 1)
	{
		ft_init(&stack_a, argc, argv);
	stack_a_print = stack_a;
	while(stack_a_print->next != NULL) //Удалить!!!!!!!!!!!
	{
		printf("index[%i] == %i\n", i, stack_a_print->nbr);
		stack_a_print = stack_a_print->next;
		i++;
	}
	printf("index[%i] == %i\n", i, stack_a_print->nbr);
	ft_lstclear_mod(&stack_a);
	}*/


/*
		printf("prev 3 -> 2 %i\n", stack_a->next->next->prev->nbr);
		printf("prev 2 -> 1 %i\n", stack_a->next->prev->nbr);
		if (stack_a->prev == NULL)
			printf("NULL");
		else 
			printf("il yq un probleme");*/