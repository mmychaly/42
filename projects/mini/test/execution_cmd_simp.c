/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_cmd_simp.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 00:53:45 by mmychaly          #+#    #+#             */
/*   Updated: 2024/10/22 04:04:13 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution_here_doc(t_data *data)
{
	char	*line;
	int		pipefd[2];


	line = NULL;
	if (pipe(pipefd) == -1)
		ft_error_exit(1); // Refaire
	line = get_next_line(0);
	while (line != NULL)
	{
		if ((ft_strncmp(data->cmd[data->i]->here_doc_file, line, ft_strlen(line) - 1)) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	close(pipefd[1]);
	data->here_doc_pfd = pipefd[0];
}

void	redirection_input(t_data *data, int pipefd[2])
{
	if (data->cmd[data->i]->pos_here_doc > data->cmd[data->i]->pos_input)
		ft_redirection_here_doc(data, pipefd);
	else if (data->cmd[data->i]->pos_here_doc < data->cmd[data->i]->pos_input)
		ft_redirection_in(data, pipefd);
	else if (data->cmd[data->i]->here_doc_file == NULL && data->cmd[data->i]->input_file == NULL && data->prev_pipe != -1)
		ft_redirection_pipe(data, pipefd);
	else
	{
		if (data->i != data->nb_pipe)
    		close(pipefd[0]);
	}
}

void	redirection_output(t_data *data, int pipefd[2])
{
	if (data->cmd[data->i]->output_file != NULL || data->cmd[data->i]->append_file != NULL)
		ft_redirection_out_cmd(data, pipefd);
	else if (data->cmd[data->i]->output_file == NULL && data->cmd[data->i]->append_file == NULL && data->i != data->nb_pipe)
		ft_redirection_out_pipe(data, pipefd);
	else
	{
		if (data->i != data->nb_pipe)
    		close(pipefd[1]);
	}
}

void	ft_launch_cmd(t_data *data, int pipefd[2])
{
	char	**strs_argv;
	char	*cmd;

	redirection_input(data, pipefd);
	redirection_output(data, pipefd);
	if (data->cmd[data->i]->cmd[0] == '\0')
		error_empty_cmd(data);
	strs_argv = join_arg(data);
	if (strs_argv == NULL)
		error_join_arg(data);
	if (access(data->cmd[data->i]->cmd, F_OK | X_OK) == 0)
		cmd = ft_strdup(data->cmd[data->i]->cmd);
	else
		cmd = ft_envp_cherch(data->cmd[data->i]->cmd, data->envp);
	if (cmd == NULL)
		free_error_cmd(strs_argv, data);
	if (execve(cmd, strs_argv, data->envp) == -1)
		free_fault_execve(strs_argv, cmd, data);
}

void	execution_cmd(t_data *data)
{
	int	pid;
	int	pipefd[2];

	data->prev_pipe = -1;
	data->here_doc_pfd = -1;
	data->i = 0;
	while (data->i <= data->nb_pipe)
	{	
		if (data->cmd[data->i]->here_doc_file != NULL)
			execution_here_doc(data);
		if (data->i != data->nb_pipe && pipe(pipefd) == -1)
		{
			write(2, "ERROR: pipe",11);
			data->exit_status = 1;
			return ;
		}
		pid = fork();
		if (pid == -1)
		{
			write(2,"ERROR: fork", 11);
			data->exit_status = 1;
			return ;
		}
		if (pid == 0)
			ft_launch_cmd(data, pipefd);
		if (data->here_doc_pfd != -1 ) //Здесь можно за одно высвобождать пайп если редирекция пошла из файла 
		{
			close(data->here_doc_pfd);
			data->here_doc_pfd = -1;
		}
		data->flag_pipe = 0;
		if (data->prev_pipe != -1)
			close(data->prev_pipe);// Проверить вовремя ли закрывает пайп из launch_here_doc
		if (data->i != data->nb_pipe)
			close(pipefd[1]);
		if (data->i == data->nb_pipe)
			data->prev_pipe = pid;
		else
			data->prev_pipe = pipefd[0];
		data->i++;
	}
	wait_processes(data);
}


/*
void	execution_here_doc(t_command *commands)
{
	char	*line;
	int		pipefd1[2];
	int		pipefd2[2];
	int		fd_in;

	line = NULL;
	if (pipe(pipefd1) == -1)
		ft_error_exit(1);
	line = get_next_line(0);
	while (line != NULL)
	{
		if ((ft_strncmp(commands->argv[1], line, ft_strlen(line) - 1)) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd1[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	close(pipefd1[1]);
	if (commands->input_file != NULL)
	{
		fd_in = open(commands->input_file, O_RDONLY, 0644);
   		if (fd_in == -1)
    	{
      		perror("Error opening input file in here_doc");
			free_pipe(pipefd1[0]);
			close(pipefd1[0]);
      		exit(EXIT_FAILURE);//Нужно продумать другой выход либо вернуть обратно в дочерний процесс
    	}
		if (pipe(pipefd2) == -1)
		{
			perror("Erorr in pipe(pipefd2) ");
			free_pipe(pipefd1[0]);
			close(pipefd1[0]);
			exit(EXIT_FAILURE); //тоже самое //другой выход 
		}
		line = get_next_line(fd_in);
		while (line != NULL)
		{
			write(pipefd2[1], line, ft_strlen(line));
			free(line);
			line = get_next_line(fd_in);
		}
		close(fd_in);
		line = get_next_line(pipefd1[0]);
		while (line != NULL)
		{
			write(pipefd2[1], line, ft_strlen(line));
			free(line);
			line = get_next_line(pipefd1[0]);
		}
		close(pipefd1[0]);
		close(pipefd2[1]);
		commands->prev_pipe = pipefd2[0];
	}
	else
		commands->prev_pipe = pipefd1[0];
}
*/

/*void	ft_launch_cmd(t_data *data)
{
	char	**strs_argv;
	char	*cmd;

	if (commands->input_file != NULL)
		ft_redirection_in(commands);
	if (commands->output_file != NULL || commands->append_file != NULL)
		ft_redirection_out_cmd(commands, 0);
	if (commands->argv[0][0] == '\0')//Как работает? 
		error_empty_cmd(0); // 0 == не включать free_pipe(0);
	strs_argv = ft_split(commands->argv[0], ' ');
	if (strs_argv == NULL)
		error_split(0);
//	strs_argv = check_strs(strs_argv, data); //пока что отключил 
//	if (strs_argv == NULL)
//		error_cmd();
	if (access(strs_argv[0], F_OK | X_OK) == 0)
		cmd = ft_strdup(strs_argv[0]);
	else
		cmd = ft_envp_cherch(strs_argv[0], commands->envp);
	if (cmd == NULL)
		free_error_cmd(strs_argv, 0);
	if (execve(cmd, strs_argv, commands->envp) == -1)
		free_fault_execve(strs_argv, cmd, 0);  
}*/