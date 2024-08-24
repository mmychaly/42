/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 23:22:04 by mmychaly          #+#    #+#             */
/*   Updated: 2024/08/25 00:38:10 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char *argv[])
{
	t_stack	*stack_a;

	if (argc > 1)
	{
		ft_init(&stack_a, argc, argv);
		ft_lstclear_mod(&stack_a);
	}
	return (0);
}
