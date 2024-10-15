/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 00:53:45 by mmychaly          #+#    #+#             */
/*   Updated: 2024/10/14 06:31:29 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	launch_here_doc(t_command *commands)
{
	char	*line;
	int		pipefd[2];

	line = NULL;
	if (pipe(pipefd) == -1)
		ft_error_exit(1);
	commands->prev_pipe = pipefd[0];
	line = get_next_line(0);
	while (line != NULL)
	{
		if ((ft_strncmp(commands->argv[1], line, ft_strlen(line) - 1)) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	close(pipefd[1]);
}

void	ft_launch_cmd(t_command *commands, int pipefd[2])
{
	char	**strs_argv;
	char	*cmd;

	close(pipefd[0]);
	close(pipefd[1]);
	if (commands->prev_pipe != -1)
		close(commands->prev_pipe);
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
}

void	ft_launch_in(t_command *commands, int pipefd[2])
{
	char	**strs_argv;
	char	*cmd;

	close(pipefd[0]);
	close(pipefd[1]);
	if (commands->prev_pipe != -1)
		close(commands->prev_pipe);
	ft_redirection_in(commands);
	if (commands->output_file != NULL || commands->append_file != NULL)
		ft_redirection_out_cmd(commands, 0);
	if (commands->argv[0][0] == '\0')
		error_empty_cmd(0);
	strs_argv = ft_split(commands->argv[0], ' ');
	if (strs_argv == NULL)
		error_split(0);
	if (access(strs_argv[0], F_OK | X_OK) == 0)
		cmd = ft_strdup(strs_argv[0]);
	else
		cmd = ft_envp_cherch(strs_argv[0], commands->envp);
	if (cmd == NULL)
		free_error_cmd(strs_argv, 0);
	if (execve(cmd, strs_argv, commands->envp) == -1)
		free_fault_execve(strs_argv, cmd, 0);  
}
void	ft_launch_here_doc(t_command *commands, int pipefd[2])
{
		char	**strs_argv;
	char	*cmd;

	close(pipefd[0]);
	close(pipefd[1]);
	ft_redirection_read_pipe(commands);
	if (commands->output_file != NULL || commands->append_file != NULL)
		ft_redirection_out_cmd(commands, 0);
	if (commands->argv[0][0] == '\0')
		error_empty_cmd(1);
	strs_argv = ft_split(commands->argv[0], ' ');
	if (strs_argv == NULL)
		error_split(1);
	if (access(strs_argv[2], F_OK | X_OK) == 0)
		cmd = ft_strdup(strs_argv[2]);
	else
		cmd = ft_envp_cherch(strs_argv[2], commands->envp);
	if (cmd == NULL)
		free_error_cmd(strs_argv, 1);
	if (execve(cmd, strs_argv, commands->envp) == -1)
		free_fault_execve(strs_argv, cmd, 1);  
}

void	execution_cmd(t_command *commands)
{
	int	pid;
	int	pipefd[2];
	int	status;

	commands->prev_pipe = -1;
	if (commands->here_doc_file != NULL)
		launch_here_doc(commands);
	if (pipe(pipefd) == -1)
		ft_error_exit(1);
	pid = fork();
	if (pid == -1)
		ft_error_exit(1);
	if (pid == 0)
	{
		if (commands->input_file == NULL && commands->here_doc_file == NULL)
			ft_launch_cmd(commands, pipefd); //Исполняем просто команду без редирекций
		else if (commands->input_file != NULL && commands->here_doc_file == NULL)
			ft_launch_in(commands, pipefd); //исполняем команду с перенаправлением из файла
		else //(commands->here_doc_file != NULL)
			ft_launch_here_doc(commands, pipefd); ////исполняем команду с перенаправлением из here_doc
	}
	if (commands->here_doc_file != -1)
		close(commands->prev_pipe);// Проверить вовремя ли закрывает пайп из launch_here_doc
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	else
		ft_error_exit(1);
}
