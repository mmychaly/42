/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 00:52:19 by artemii           #+#    #+#             */
/*   Updated: 2024/12/01 10:29:09 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	error_exit(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

char	**copy_envp(char **envp)
{
	int		i;
	int		count;
	char	**new_envp;

	count = 0;
	while (envp[count] != NULL)
		count++;
	new_envp = malloc(sizeof(char *) * (count + 1));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
		{
			while (--i >= 0)
				free(new_envp[i]);
			free(new_envp);
			return (NULL);
		}
		i++;
	}
	new_envp[count] = NULL;
	return (new_envp);
}

void	handle_signals(void)
{
	signal(SIGINT, handle_sigint_newline);
	signal(SIGQUIT, SIG_IGN);
}

void	reset_data_flags(t_data *data)
{
	data->back_in_main = 0;
	data->builtin_cmd = 0;
	data->display_builtin_cmd = 0;
}

void	handle_sigint_status(t_data *data, int *exit_status)
{
	if (g_sig == 2)
	{
		data->exit_status = 130;
		*exit_status = 130;
		g_sig = 0;
	}
}
