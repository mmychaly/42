#ifndef PIPEX_H
#define PIPEX_H
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

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

void	ft_launch_child_1(char **argv, char *envp[], int pipefd[2]);
void	ft_launch_child_2(char **argv, char *envp[], int pipefd[2]);
void	ft_redirection_in(char *argv, int pipefd);
void	ft_redirection_out(char *argv, int pipefd);

void ft_create_empty_file(char *filename);
void ft_execution(char **argv, char *envp[]);
void	ft_free_strs(char **strs);
#endif