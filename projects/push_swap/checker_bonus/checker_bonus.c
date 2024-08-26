/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 03:44:04 by mmychaly          #+#    #+#             */
/*   Updated: 2024/08/26 04:32:08 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

char	*ft_launch_operations(char *str, t_stack **stack_a, t_stack **stack_b)
{
	int	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	if (ft_launch_s(str, len, stack_a, stack_b) == 1)
		return (get_next_line(0));
	else if (ft_launch_r(str, len, stack_a, stack_b) == 1)
		return (get_next_line(0));
	else if (ft_launch_rrr(str, len, stack_a, stack_b) == 1)
		return (get_next_line(0));
	else if (ft_launch_p(str, len, stack_a, stack_b) == 1)
		return (get_next_line(0));
	else
		free_all_exit(str, stack_a, stack_b);
	return (get_next_line(0));
}

void	ft_check_operation(t_stack **stack_a, char *str, int len)
{
	t_stack	*stack_b;
	char	*temp;

	stack_b = NULL;
	while (str != NULL)
	{
		temp = str;
		str = ft_launch_operations(str, stack_a, &stack_b);
		if (str != NULL)
			free(temp);
		else
			break ;
	}
	if (stack_b != NULL || ft_check_sort(*stack_a, len) == 0)
		write(1, "KO\n", 3);
	else
		write(1, "OK\n", 3);
	if (stack_b != NULL)
		ft_lstclear_mod(&stack_b);
	if (str != NULL)
		free(str);
}

int	main(int argc, char *argv[])
{
	t_stack	*stack_a;
	char	*str;
	int		len;

	if (argc > 1)
	{
		len = ft_init_bonus(&stack_a, argc, argv);
		str = get_next_line(0);
		if (str == NULL && ft_check_sort(stack_a, len) == 0)
			write(1, "KO\n", 3);
		else if (str == NULL && ft_check_sort(stack_a, len) == 1)
			write(1, "OK\n", 3);
		else
			ft_check_operation(&stack_a, str, len);
		str = get_next_line(0);
		if (str != NULL)
			free(str);
		ft_lstclear_mod(&stack_a);
	}
	return (0);
}
