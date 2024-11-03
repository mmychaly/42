/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_cmd_simp.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 00:53:45 by mmychaly          #+#    #+#             */
/*   Updated: 2024/11/03 18:06:34 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *get_line() {
    char *buffer = malloc(256); // Простое выделение памяти для строки
    if (!buffer) 
		return NULL;
    ssize_t n = read(0, buffer, 255); // Чтение из stdin
    if (n <= 0) 
	{
        free(buffer);
        return NULL; // Если ничего не прочитано, возвращаем NULL
    }
    buffer[n] = '\0'; // Завершаем строку
    return buffer;
}

void	execution_here_doc(t_data *data)
{
	char	*line;
	int		pipefd[2];

	g_pid = -5;
	data->heredoc_interrupted = 0;
	line = NULL;
	if (pipe(pipefd) == -1)
		return ;
	while (1)
	{
	    line = get_line();
        if (g_pid == -10) 
		{
			close(pipefd[1]);
			free_pipe(pipefd[0]);
            close(pipefd[0]);
            free(line); // Освобождаем память, если она была выделена
			g_pid = -1;
			data->exit_status = 150;
			printf("execution_here_doc\n");
            return; // Выходим из функции
        }
		if (line == NULL) {
           break; // Выходим, если достигнут конец ввода
        }
        // Проверяем, достигли ли конца here_doc
       if (ft_strncmp(data->cmd[data->i]->here_doc_file, line, ft_strlen(line) - 1) == 0) {
            free(line);
            break;
        }

        // Записываем в пайп
        write(pipefd[1], line, ft_strlen(line));
        free(line);
	}
	data->heredoc_interrupted = 1;
	close(pipefd[1]);
	data->here_doc_pfd = pipefd[0];
	g_pid = -1;
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
	char	*cmd;

	redirection_input(data, pipefd);
	redirection_output(data, pipefd);
	if (data->cmd[data->i]->cmd_arg[1] != NULL)//Вставь сюда вторую строку из массива аргументов -v
	{
		if (access(data->cmd[data->i]->cmd_arg[1], F_OK) == 0)  //тоже самое -v
		{
			if (data->flag_pipe == 1)
				free_pipe(0);
       		if (access(data->cmd[data->i]->cmd_arg[1], R_OK) == -1)//тоже самое -v
      	  	{
				write(2, "Error file in arg :Permission denied\n", 37);
				free_data(data);
				exit(1);
			}
   		}
	}
	if (data->cmd[data->i]->cmd[0] == '\0')
		error_empty_cmd(data);
	if (access(data->cmd[data->i]->cmd, F_OK | X_OK) == 0)
		cmd = ft_strdup(data->cmd[data->i]->cmd);
	else
		cmd = ft_envp_cherch(data->cmd[data->i]->cmd, data->envp);
	if (cmd == NULL)
		free_error_cmd(data);//Переделай функции убери strs_argv -v
	if (execve(cmd, data->cmd[data->i]->cmd_arg, data->envp) == -1)//Вместо strs_argv поставь масив для аргументов -v
		free_fault_execve(cmd, data);//Переделай функции убери strs_argv -v
}

void	execution_cmd(t_data *data)
{
	int pid;
	int	pipefd[2];

	data->prev_pipe = -1;
	data->here_doc_pfd = -1;
	data->i = 0;
	data->flag_pipe = 0;
//	g_pid = -1;
	while (data->i <= data->nb_pipe)
	{	
		if (data->cmd[data->i]->here_doc_file != NULL)
		{
			execution_here_doc(data);
			if (data->heredoc_interrupted != 1)
				return ;
			if (data->here_doc_pfd == -1)
				write(2, "ERROR in here_doc\n", 18);
		}
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
		{
//			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			ft_launch_cmd(data, pipefd);
		}
		else
			g_pid = pid;
		if (data->here_doc_pfd != -1 ) //Нужно ли высвобожать пайп в родительском если это уже сделанно в дочернем?
		{
			close(data->here_doc_pfd);
			data->here_doc_pfd = -1;
		}
		data->flag_pipe = 0;
		if (data->prev_pipe != -1)
			close(data->prev_pipe);
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
