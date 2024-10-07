/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:44:20 by mmychaly          #+#    #+#             */
/*   Updated: 2024/10/02 06:38:13 by mmychaly         ###   ########.fr       */
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
# include "libft/libft.h"

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

void	ft_execution(int nbr_cmd, char **argv, char *envp[]);
void	ft_launch_child_1(int i, char **argv, char *envp[], int pipefd[2]);
void	ft_launch_child_2(int i, char **argv, char *envp[], int prev_pipe);
void	ft_redirection_in(char *argv, int pipefd);
void	ft_redirection_out(char *argv, int pipefd);
void	ft_launch_other(int i, char **argv, char *envp[], int pipefd[2], int prev_pipe);
void	ft_redirection_between(int pipefd, int prev_pipe);

void	free_fault_cmd(char **strs);
void	free_fault_execve(char **strs, char *cmd);
void	ft_free_strs(char **strs);
void	ft_error_exit(int nb);
#endif