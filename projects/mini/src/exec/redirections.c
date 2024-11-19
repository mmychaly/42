/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 00:47:25 by artemii           #+#    #+#             */
/*   Updated: 2024/11/19 17:25:31 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void ft_redirection_in(t_data *data)
{
    int fd_in;
    
    if(data->prev_pipe != -1)
    {
        free_pipe(data->prev_pipe);
		close(data->prev_pipe);
    }
    if(data->cmd[data->i]->here_doc_pfd != 0)
    {
        free_pipe(data->cmd[data->i]->here_doc_pfd);
		close(data->cmd[data->i]->here_doc_pfd);
        data->cmd[data->i]->here_doc_pfd = 0;
    }
    if (data->i != data->nb_pipe)
        close(data->pipefd[0]);
    fd_in = open(data->cmd[data->i]->input_file, O_RDONLY, 0644);
    if (fd_in == -1)
    {
        perror("Error opening input file");
        if (data->i != data->nb_pipe)
            close(data->pipefd[1]);
        free_data_cmd(data);
        exit(EXIT_FAILURE);
    }
    if (data->nb_pipe == 0 && data->builtin_cmd == 1)
        close(fd_in);
    else
    {
        if (dup2(fd_in, STDIN_FILENO) == -1)
        {
        perror("Error duplicating file descriptor for input");
        if (data->i != data->nb_pipe)
            close(data->pipefd[1]);
        close(fd_in);
        free_all_data(data);
        exit(EXIT_FAILURE);
        }
        close(fd_in); // Закрываем дескриптор файла после перенаправления
        data->flag_pipe = 0;
    }
}

void	ft_redirection_here_doc(t_data *data)
{
    int fd_in;

    if(data->prev_pipe != -1)
    {
        free_pipe(data->prev_pipe);
		close(data->prev_pipe);
    }
    if (data->i != data->nb_pipe)
    {
        close(data->pipefd[0]);
    }
    if (data->cmd[data->i]->input_file != NULL)
    {
        fd_in = open(data->cmd[data->i]->input_file, O_RDONLY, 0644);
        if (fd_in == -1)
        {
            perror("Error opening input file:");
            free_pipe(data->cmd[data->i]->here_doc_pfd);
		    close(data->cmd[data->i]->here_doc_pfd);
            data->cmd[data->i]->here_doc_pfd = 0;
            if (data->i != data->nb_pipe)
                close(data->pipefd[1]);
            free_all_data(data);
            exit (EXIT_FAILURE);
        }
        close(fd_in);
    }
    if (data->nb_pipe == 0 && data->builtin_cmd == 1)
    {
        free_pipe(data->cmd[data->i]->here_doc_pfd);
    	close(data->cmd[data->i]->here_doc_pfd);
        data->cmd[data->i]->here_doc_pfd = 0;
    }
    else
    {
	    if (dup2(data->cmd[data->i]->here_doc_pfd, STDIN_FILENO) == -1)
	    {
    		perror("Error: dup2 prev_pipe");
    		free_pipe(data->cmd[data->i]->here_doc_pfd);
    		close(data->cmd[data->i]->here_doc_pfd);
            data->cmd[data->i]->here_doc_pfd = 0;
            if (data->i != data->nb_pipe)
                close(data->pipefd[1]);
            free_all_data(data);
    		exit (EXIT_FAILURE);
	    }
        close(data->cmd[data->i]->here_doc_pfd);
        data->cmd[data->i]->here_doc_pfd = 0;
        data->flag_pipe = 1;
    }
}

void	ft_redirection_pipe(t_data *data)
{
    if (data->i != data->nb_pipe)
        close(data->pipefd[0]);
    if (dup2(data->prev_pipe, STDIN_FILENO) == -1)
	{
		perror("Error: dup2 prev_pipe");
		free_pipe(data->prev_pipe);
		close(data->prev_pipe);
        if (data->i != data->nb_pipe)
            close(data->pipefd[1]);
        free_all_data(data);
		exit (EXIT_FAILURE);
	}
	close(data->prev_pipe);
    data->flag_pipe = 1;
}

void	ft_redirection_out_cmd(t_data *data)
{
	int	fd_out;
    if (data->nb_pipe == 0 && data->builtin_cmd == 1 && data->display_builtin_cmd == 1)
        data->std_out = dup(1);
    if (data->i != data->nb_pipe)
    {
        close(data->pipefd[1]);
    }
	if (data->cmd[data->i]->pos_append > data->cmd[data->i]->pos_output)
    {
        if (data->cmd[data->i]->output_file != NULL)
        {
            fd_out = open(data->cmd[data->i]->output_file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
            if (fd_out == -1)
            {
                if (data->flag_pipe > 0)
		            error_open_outfile(1, data);
                else
                    error_open_outfile(0, data);
            }
            close(fd_out);
        }
		fd_out = open(data->cmd[data->i]->append_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    }
	else
    {
        if (data->cmd[data->i]->append_file != NULL)
        {
            fd_out = open(data->cmd[data->i]->append_file, O_WRONLY | O_CREAT | O_APPEND, 0644);;
            if (fd_out == -1)
            {
                if (data->flag_pipe > 0)
		            error_open_outfile(1, data);
                else
                    error_open_outfile(0, data);
            }
            close(fd_out);
        }
		fd_out = open(data->cmd[data->i]->output_file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
    }
	if (fd_out == -1)
    {
        if (data->flag_pipe > 0)
		    error_open_outfile(1, data);
        else
            error_open_outfile(0, data);
    }
    if (data->nb_pipe == 0 && data->builtin_cmd == 1 && data->display_builtin_cmd != 1)
        	close(fd_out);
    else
    {
	    if (dup2(fd_out, STDOUT_FILENO) == -1)
	    {
		    perror("dup2 fd_out");
            if (data->flag_pipe > 0)
		      free_pipe(0);
		    close(fd_out);
          free_all_data(data);
		    exit (EXIT_FAILURE);
	    }
        close(fd_out);
    }
}

void    ft_redirection_out_pipe(t_data *data)
{
    if (dup2(data->pipefd[1], STDOUT_FILENO) == -1)
	{
		perror("Error: dup2 pipefd[1]");
        if (data->flag_pipe > 0)
		    free_pipe(0);
		close(data->pipefd[1]);
        free_all_data(data);
		exit (EXIT_FAILURE);
	}
    close(data->pipefd[1]);
}
