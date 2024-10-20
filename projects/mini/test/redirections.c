/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 00:47:25 by artemii           #+#    #+#             */
/*   Updated: 2024/10/20 18:20:09 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_redirection_in(t_data *data, int pipefd[2])
{
    int fd_in;
    
    if(data->prev_pipe != -1)
    {
        free_pipe(data->prev_pipe);
		close(data->prev_pipe);
    }
    if(data->here_doc_pfd != -1)
    {
        free_pipe(data->here_doc_pfd);
		close(data->here_doc_pfd);
    }
    if (data->i != data->nb_pipe)
        close(pipefd[0]);
    fd_in = open(data->cmd[data->i]->input_file, O_RDONLY, 0644);
    if (fd_in == -1)
    {
        perror("Error opening input file");
        if (data->i != data->nb_pipe)
            close(pipefd[1]);
        exit(EXIT_FAILURE); //Trouver l'autre solution
    }
    if (dup2(fd_in, STDIN_FILENO) == -1)
    {
        perror("Error duplicating file descriptor for input");
        if (data->i != data->nb_pipe)
            close(pipefd[1]);
        close(fd_in);
        exit(EXIT_FAILURE); //Trouver l'autre solution
    }
    close(fd_in); // Закрываем дескриптор файла после перенаправления
}

void	ft_redirection_here_doc(t_data *data, int pipefd[2])
{
    if(data->prev_pipe != -1)
    {
        free_pipe(data->prev_pipe);
		close(data->prev_pipe);
    }
    if (data->i != data->nb_pipe)
        close(pipefd[0]);
	if (dup2(data->here_doc_pfd, STDIN_FILENO) == -1)
	{
		perror("Error: dup2 prev_pipe");
		free_pipe(data->here_doc_pfd);
		close(data->here_doc_pfd);
        if (data->i != data->nb_pipe)
            close(pipefd[1]);
		exit (EXIT_FAILURE);
	}
	close(data->here_doc_pfd);
}

void	ft_redirection_pipe(t_data *data, int pipefd[2])
{
    if (data->i != data->nb_pipe)
        close(pipefd[0]);
    if (dup2(data->prev_pipe, STDIN_FILENO) == -1)
	{
		perror("Error: dup2 prev_pipe");
		free_pipe(data->prev_pipe);
		close(data->prev_pipe);
        if (data->i != data->nb_pipe)
            close(pipefd[1]);
		exit (EXIT_FAILURE); //Trouver l'autre solution
	}
	close(data->prev_pipe);
}

void	ft_redirection_out_cmd(t_data *data, int flag_pipe)
{
	int	fd_out;
    
	if (commands->append_file != NULL)
		fd_out = open(commands->append_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd_out = open(commands->output_file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd_out == -1)
    {
        if (flag_pipe == 1)
		    error_open_outfile(1); //По идеи здесь без 1 так как данные выводим из команды и нет необходимости высвобождать пайп
        else
            error_open_outfile(0);
    }
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