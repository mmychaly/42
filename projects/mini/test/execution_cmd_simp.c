/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_cmd_simp.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 00:53:45 by mmychaly          #+#    #+#             */
/*   Updated: 2024/10/19 01:05:34 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	*cat;

	cat = "/bin/cat";
	ft_redirection_read_pipe(commands);
	if (commands->output_file != NULL || commands->append_file != NULL)
		ft_redirection_out_cmd(commands, 1);
	if (commands->argv[2] == NULL)
	{
		execve(cat, NULL, NULL); //NULL? вместо второго аргумента
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