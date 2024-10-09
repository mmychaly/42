/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:44:20 by mmychaly          #+#    #+#             */
/*   Updated: 2024/10/09 23:46:47 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdlib.h>
# include "../libft/libft.h"

typedef struct s_data
{
	char	**argv;
	char	**envp;
	int		nbr_cmd;
	int		prev_pipe;
	int		i;
	int		flag;
	int		nbr_strs;
}				t_data;

int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*get_next_line(int fd);
void	launch_here_doc(char **argv, int pipefd[2]);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strdup(const char *s);
char	*ft_envp_cherch(char *cmd, char **envp);
char	*ft_creat_path(char **strs, char *cmd);
void	ft_add_cmd(char **strs, char *cmd);
void	ft_add_symb(char **strs);
void	execution(t_data *data);
void	execution_here_doc(t_data *data);
void	execute_child(t_data *data, int pipefd[2]);
void	execute_child_here_doc(t_data *data, int pipefd[2]);
void	wait_processes(t_data *data);
void	ft_launch_child_1(t_data *data, int pipefd[2]);
void	ft_launch_child_2(t_data *data);
void	ft_launch_other(t_data *data, int pipefd[2]);
void	ft_redirection_in(char *argv, int pipefd);
void	ft_redirection_out(char *argv, t_data *data, int flag);
void	ft_redirection_between(int pipefd, t_data *data);
char	**check_strs(char **strs_argv, t_data *data);
void	free_fault_cmd(char **strs);
void	free_fault_execve(char **strs, char *cmd);
void	ft_free_strs(char **strs);
void	ft_error_exit(int nb);
void	error_empty_cmd(void);
void	error_cmd(void);
void	free_error_cmd(char **strs_argv);
void	error_open_outfile(int pipefd);
void	error_dup2_out(int prev_pipe);
void	free_pipe(int fd);
void	error_split(void);
#endif