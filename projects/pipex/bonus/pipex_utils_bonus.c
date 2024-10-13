/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 04:06:07 by mmychaly          #+#    #+#             */
/*   Updated: 2024/10/13 15:19:51 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**check_strs(char **strs_argv, t_data *data)
{
	char	**strs;
	char	*option;
	char	*temp;

	data->nbr_strs = 0;
	while (strs_argv[data->nbr_strs] != NULL)
		data->nbr_strs++;
	if (data->nbr_strs <= 2)
		return (strs_argv);
	temp = ft_strchr(data->argv[data->i], '\'');
	option = ft_strdup(temp + 1);
	if (option == NULL)
		return (ft_free_strs(strs_argv), NULL);
	option[ft_strlen(option) - 1] = '\0';
	temp = ft_strdup(strs_argv[0]);
	if (temp == NULL)
		return (free(option), ft_free_strs(strs_argv), NULL);
	ft_free_strs(strs_argv);
	strs = malloc(sizeof(char *) * 3);
	if (strs == NULL)
		return (free(temp), free(option), NULL);
	strs[0] = temp;
	strs[1] = option;
	strs[2] = NULL;
	return (strs);
}

void	wait_processes(t_data *data)
{
	int	pid;
	int	status;

	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		if (pid == data->prev_pipe)
		{
			if (WIFEXITED(status))
				exit(WEXITSTATUS(status));
			else
				ft_error_exit(1);
		}
		pid = waitpid(-1, &status, 0);
	}
}

void	exit_error_argum(void)
{
	write(2, "Error: Incorrect number of arguments\n", 37);
	exit(EXIT_FAILURE);
}
