/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 03:09:52 by mmychaly          #+#    #+#             */
/*   Updated: 2024/08/26 03:09:56 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_BONUS_H
# define CHECKER_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_stack
{
	int				nbr;
	int				index;
	int				above_mid;
	int				nbr_oper;
	struct s_stack	*next;
	struct s_stack	*prev;
}				t_stack;

char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
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
int		ft_init_bonus(t_stack **stack, int argc, char *argv[]);
void	ft_creat_stack(t_stack **stack, int *array, int len_stack);
int		*ft_creat_int_array(char **strs, int len_stack);
int		ft_atoi_mod(const char *nptr, char **strs, int *array);
char	**ft_manual_split(int argc, char **argv);
void	free_all_exit(char *str, t_stack **stack_a, t_stack **stack_b);
void	ft_swap(t_stack **stack_a);
void	ft_rotate(t_stack **stack_a);
void	ft_rev_rotate(t_stack **stack_a);
void	ft_push(t_stack **stack_a, t_stack **stack_b);
void	ft_push_part_2(t_stack **src, t_stack **dest, t_stack *f, t_stack *s);
void	ft_rotate_all(t_stack **stack_a, t_stack **stack_b);
void	ft_rev_rotate_all(t_stack **stack_a, t_stack **stack_b);
void	ft_swap_all(t_stack **stack_a, t_stack **stack_b);
int		ft_check_sort(t_stack *stack, int len);
void	check_index(t_stack **stack);
void	ft_check_operation(t_stack **stack_a, char *str, int len);
char	*ft_launch_operations(char *str, t_stack **stack_a, t_stack **stack_b);
int		ft_launch_s(char *str, int len, t_stack **stack_a, t_stack **stack_b);
int		ft_launch_r(char *str, int len, t_stack **stack_a, t_stack **stack_b);
int		ft_launch_rrr(char *str, int len, t_stack **stack_a, t_stack **stack_b);
int		ft_launch_p(char *str, int len, t_stack **stack_a, t_stack **stack_b);
#endif