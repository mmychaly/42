/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:27:49 by mmychaly          #+#    #+#             */
/*   Updated: 2024/10/05 03:38:09 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	execution(int nbr_cmd, int flag, char **argv, char *envp[])
{
	int	pid;
	int	pipefd[2];
	int prev_pipe;
	int	status;
	int i;

	i = 2;
	prev_pipe = -1;
	while (i < nbr_cmd + 2 )
	{
		if (i != nbr_cmd + 1 && pipe(pipefd) == -1)
			ft_error_exit(1);
		pid = fork();
		if (pid == -1)
			ft_error_exit(1);
		printf("pid == %i\n", pid); // Supprimer 
		if (pid == 0)
		{
			if (i == 2 && flag == 1)
				launch_here_doc(argv, pipefd);
			else if ( i == 2 && flag == 0)
				ft_launch_child_1(i, argv, envp, pipefd);
			else if (i == nbr_cmd + 1)
				ft_launch_child_2(i, argv, envp, prev_pipe);
			else
				ft_launch_other(argv[i], envp, pipefd, prev_pipe);
		}
		if (prev_pipe != -1)
			close(prev_pipe);
		if (i != nbr_cmd + 1)
			close(pipefd[1]);
		prev_pipe = pipefd[0];
		if (i == nbr_cmd + 1)
			prev_pipe = pid; 
		i++;
	}
	while ((pid = waitpid(-1, &status, 0)) > 0)
	{
		if (pid == prev_pipe)
		{
			printf("exit prev_pipe == %i\n", prev_pipe);
			if (WIFEXITED(status))
				exit(WEXITSTATUS(status));
			else
				ft_error_exit(1);
		}
	}
}

int	main(int argc, char **argv, char *envp[])
{
	int	nbr_cmd;
	int flag;

	flag = 0;
	nbr_cmd = argc - 3;
	if (envp == NULL)
	{
		write(2, "Error: envp\n", 12);
		exit (EXIT_FAILURE);
	}
	if ((ft_strncmp(argv[1], "here_doc", strlen(argv[1]))) == 0 && argc >= 6)
	{
		flag = 1;
		execution(nbr_cmd, flag, argv, envp);
	}
	else if (argc >= 5)
		execution(nbr_cmd, flag, argv, envp);
	else
	{
		write(2, "Error: Incorrect number of arguments\n", 37);
		exit (EXIT_FAILURE);
	}
	return (0);
}
