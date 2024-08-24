/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 23:07:00 by mmychaly          #+#    #+#             */
/*   Updated: 2024/08/25 01:41:43 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_stack
{
	int				nbr;
	int				index;
	int				above_mid;
	int				nbr_oper;
	struct s_stack	*next;
	struct s_stack	*prev;
}				t_stack;

int		ft_isdigit(int c);
char	*ft_strdup(const char *s);
char	**ft_split(char const *s, char c);
void	ft_error_exit(int nbr);
void	ft_free_strs(char **strs);
void	ft_free_error_exit(char **strs);
void	ft_check_digit(char **strs);
void	ft_chek_double(int *array, int len_stack);
t_stack	*ft_lstnew_mod(int data);
void	ft_lstadd_back_mod(t_stack **lst, t_stack *new);
t_stack	*ft_lstlast_mod(t_stack *lst);
void	ft_lstclear_mod(t_stack **lst);
void	ft_error_lstclear(t_stack **lst);
void	ft_init(t_stack **stack, int argc, char *argv[]);
void	ft_creat_stack(t_stack **stack, int *array, int len_stack);
int		*ft_creat_int_array(char **strs, int len_stack);
int		ft_atoi_mod(const char *nptr, char **strs, int *array);
char	**ft_manual_split(int argc, char **argv);
void	ft_stack_check(t_stack **stack_a, int a, t_stack **stack_b, int b);
void	ft_stack_over_three(t_stack **stack_a, int a, t_stack **stack_b, int b);
void	ft_push_stack_b(t_stack **stack_a, int *a, t_stack **stack_b, int *b);
void	ft_sort_three(t_stack **stack_a, int len_a);
void	ft_push_back(t_stack **stack_a, t_stack **stack_b, int a, int b);
int		ft_check_sort(t_stack *stack, int len);
void	check_min_max(t_stack *stack_a, t_stack **min, t_stack **max);
void	check_index(t_stack **stack);
void	ft_find_pos(t_stack **stack_a, int top_b);
void	ft_check_midl(t_stack **stack);
void	ft_sort_a(t_stack **stack_a, t_stack *min, t_stack *max);
void	ft_swap(t_stack **stack_a);
void	ft_rotate(t_stack **stack_a);
void	ft_rev_rotate(t_stack **stack_a);
void	ft_push(t_stack **stack_a, t_stack **stack_b);
void	ft_push_part_2(t_stack **src, t_stack **dest, t_stack *f, t_stack *s);
void	ft_rotate_all(t_stack **stack_a, t_stack **stack_b);
void	ft_rev_rotate_all(t_stack **stack_a, t_stack **stack_b);
void	ft_display_and_start_sa(t_stack **stack_a);
void	ft_display_and_start_ra(t_stack **stack_a);
void	ft_display_and_start_rra(t_stack **stack_a);
void	ft_display_and_start_rb(t_stack **stack_b);
void	ft_display_and_start_rrb(t_stack **stack_b);
void	ft_display_and_start_pa(t_stack **stack_b, t_stack **stack_a);
void	ft_display_and_start_pb(t_stack **stack_a, t_stack **stack_b);
void	ft_find_best_elem(t_stack **stack_a, t_stack **stack_b);
void	ft_count_operation_1(t_stack *actuel_a, t_stack **stack);
void	ft_count_operation_2(t_stack *actuel_a, t_stack **stack);
int		check_comp_elem(int nbr, t_stack *stack_b);
void	ft_find_max_elem(t_stack *stack, t_stack **max);
void	ft_find_under(t_stack **stack, int nbr, t_stack **under);
int		ft_count_total(int ra, int rra, int rb, int rrb);
int		ft_count_left_top_ra_a(t_stack *actual);
int		ft_count_left_top_rra_a(t_stack *actual);
int		ft_count_left_top_rrb_b(t_stack *actual);
int		ft_count_left_top_rb_b(t_stack *actual);
void	ft_prepar_stack(t_stack **stack_a, t_stack **stack_b);
void	ft_change_position_1(t_stack *el, t_stack **stack_a, t_stack **stack_b);
void	ft_change_position_2(t_stack *el, t_stack **stack_a, t_stack **stack_b);
void	ft_check_best_elem(t_stack *stack, t_stack **best);
void	ft_count_rr(t_stack **stack_a, t_stack **stack_b, int ra, int rb);
void	ft_count_rrr(t_stack **stack_a, t_stack **stack_b, int rra, int rrb);
int		ft_display_launch_last_rr(t_stack **stack_a, t_stack **stack_b, int rr);
int		ft_display_launch_last_ra(t_stack **stack_a, int ra);
int		ft_display_launch_last_rb(t_stack **stack_b, int rb);
int		ft_display_launch_last_rrr(t_stack **stk_a, t_stack **stk_b, int rrr);
int		ft_display_launch_last_rra(t_stack **stack_a, int rra);
int		ft_display_launch_last_rrb(t_stack **stack_b, int rrb);
void	check_bigger_in_a(t_stack *actuel, t_stack **pos, int top_b);
#endif