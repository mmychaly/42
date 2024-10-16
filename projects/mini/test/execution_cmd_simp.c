/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_cmd_simp.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 00:53:45 by mmychaly          #+#    #+#             */
/*   Updated: 2024/10/16 19:44:02 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution_here_doc(t_command *commands)
{
	char	*line;
	int		pipefd1[2];
	int		pipefd1[2];
	int		fd_in;

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
	if (commands->input_file != NULL)
	{
		fd_in = open()
	}
}

void	ft_launch_cmd(t_command *commands)
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
}

void	ft_launch_here_doc(t_command *commands)
{
		char	**strs_argv;
	char	*cmd;

	ft_redirection_read_pipe(commands);
	if (commands->output_file != NULL || commands->append_file != NULL)
		ft_redirection_out_cmd(commands, 1);
	if (commands->argv[2] == NULL)
	{
		execve("cat", "cat", NULL);
	}	
	if (commands->argv[2][0] == '\0')
		error_empty_cmd(1);
	strs_argv = ft_split(commands->argv[2], ' ');
	if (strs_argv == NULL)
		error_split(1);
	if (access(strs_argv[0], F_OK | X_OK) == 0)
		cmd = ft_strdup(strs_argv[0]);
	else
		cmd = ft_envp_cherch(strs_argv[0], commands->envp);
	if (cmd == NULL)
		free_error_cmd(strs_argv, 1);
	if (execve(cmd, strs_argv, commands->envp) == -1)
		free_fault_execve(strs_argv, cmd, 1);  
}

void	execution_cmd(t_command *commands)
{
	int	pid;
	int	status;

	commands->prev_pipe = -1;
	if (commands->here_doc_file != NULL)
		execution_here_doc(commands);
	pid = fork();
	if (pid == -1)
		ft_error_exit(1);
	if (pid == 0)
	{
		if (commands->here_doc_file == NULL)
			ft_launch_cmd(commands); //Исполняем просто команду here_doc
		else //(commands->here_doc_file != NULL)
			ft_launch_here_doc(commands); ////исполняем команду с перенаправлением из here_doc
	}
	if (commands->prev_pipe != -1)
		close(commands->prev_pipe);// Проверить вовремя ли закрывает пайп из launch_here_doc
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status)); //Ca fermera minishell completment ou que pipex 
	else
		ft_error_exit(1);
}


/*gerer 
< infile << LIM cat */