/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 00:47:25 by artemii           #+#    #+#             */
/*   Updated: 2024/10/14 06:25:14 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void ft_redirection_in(t_command *commands)
{
    int fd_in;
 
    fd_in = open(commands->input_file, O_RDONLY, 0644);
    if (fd_in == -1)
    {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }
    if (dup2(fd_in, STDIN_FILENO) == -1)
    {
        perror("Error duplicating file descriptor for input");
        close(fd_in);
        exit(EXIT_FAILURE);
    }
    close(fd_in); // Закрываем дескриптор файла после перенаправления
}

void	ft_redirection_out_cmd(t_command *commands, int flag_pipe)
{
	int	fd_out;
    
	if (commands->append_file != NULL)
		fd_out = open(commands->append_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd_out = open(commands->output_file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd_out == -1)
		error_open_outfile(commands->prev_pipe, 1);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		perror("dup2 fd_out");
        if (flag_pipe == 1)
		    free_pipe(0);
		close(fd_out);
		exit (EXIT_FAILURE);
	}
	close(fd_out);
}

void	ft_redirection_read_pipe(t_command *commands)
{
	if (dup2(commands->prev_pipe, STDIN_FILENO) == -1)
	{
		perror("Error: dup2 prev_pipe");
		free_pipe(commands->prev_pipe);
		close(commands->prev_pipe);
		exit (EXIT_FAILURE);
	}
	close(commands->prev_pipe);
}

/*void ft_redirection_out_append(char *output_file)
{
    int fd_out = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd_out == -1)
    {
        perror("Error opening output file in append mode");
        exit(EXIT_FAILURE);
    }
    if (dup2(fd_out, STDOUT_FILENO) == -1)
    {
        perror("Error duplicating file descriptor for append output");
        close(fd_out);
        exit(EXIT_FAILURE);
    }
    close(fd_out); // Закрываем дескриптор файла после перенаправления
}

void ft_redirection_out(char *output_file)
{
    int fd_out = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_out == -1)
    {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }
    if (dup2(fd_out, STDOUT_FILENO) == -1)
    {
        perror("Error duplicating file descriptor for output");
        close(fd_out);
        exit(EXIT_FAILURE);
    }
    close(fd_out); // Закрываем дескриптор файла после перенаправления
}*/