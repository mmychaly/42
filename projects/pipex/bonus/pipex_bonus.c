/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:27:49 by mmychaly          #+#    #+#             */
/*   Updated: 2024/10/09 23:21:04 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	execute_child(t_data *data, int pipefd[2])
{
	if (data->i == 2)
		ft_launch_child_1(data, pipefd);
	else if (data->i == data->nbr_cmd + 1)
		ft_launch_child_2(data);
	else
		ft_launch_other(data, pipefd);
}

void	execute_child_here_doc(t_data *data, int pipefd[2])
{
	if (data->i == 2)
		launch_here_doc(data->argv, pipefd);
	else if (data->i == data->nbr_cmd + 1)
		ft_launch_child_2(data);
	else
		ft_launch_other(data, pipefd);
}

void	execution(t_data *data)
{
	int	pipefd[2];
	int	pid;

	data->i = 2;
	data->prev_pipe = -1;
	while (data->i < data->nbr_cmd + 2)
	{
		if (data->i != data->nbr_cmd + 1 && pipe(pipefd) == -1)
			ft_error_exit(1);
		pid = fork();
		if (pid == -1)
			ft_error_exit(1);
		if (pid == 0)
			execute_child(data, pipefd);
		if (data->prev_pipe != -1)
			close(data->prev_pipe);
		if (data->i != data->nbr_cmd + 1)
			close(pipefd[1]);
		if (data->i == data->nbr_cmd + 1)
			data->prev_pipe = pid;
		else
			data->prev_pipe = pipefd[0];
		data->i++;
	}
	wait_processes(data);
}

void	execution_here_doc(t_data *data)
{
	int	pipefd[2];
	int	pid;

	data->i = 2;
	data->prev_pipe = -1;
	while (data->i < data->nbr_cmd + 2)
	{
		if (data->i != data->nbr_cmd + 1 && pipe(pipefd) == -1)
			ft_error_exit(1);
		pid = fork();
		if (pid == -1)
			ft_error_exit(1);
		if (pid == 0)
			execute_child_here_doc(data, pipefd);
		if (data->prev_pipe != -1)
			close(data->prev_pipe);
		if (data->i != data->nbr_cmd + 1)
			close(pipefd[1]);
		if (data->i == data->nbr_cmd + 1)
			data->prev_pipe = pid;
		else
			data->prev_pipe = pipefd[0];
		data->i++;
	}
	wait_processes(data);
}

int	main(int argc, char **argv, char *envp[])
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	data.nbr_cmd = argc - 3;
	data.argv = argv;
	data.envp = envp;
	if (envp == NULL || envp[0][0] == '\0')
	{
		write(2, "Error: empty envp\n", 18);
		exit(EXIT_FAILURE);
	}
	if ((ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1]))) == 0 && argc >= 6)
		execution_here_doc(&data);
	else if ((ft_strncmp(argv[1], "here_doc",
				ft_strlen(argv[1]))) != 0 && argc >= 5)
		execution(&data);
	else
	{
		write(2, "Error: Incorrect number of arguments\n", 37);
		exit(EXIT_FAILURE);
	}
	return (0);
}
