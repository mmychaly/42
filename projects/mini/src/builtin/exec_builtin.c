/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 04:50:13 by mmychaly          #+#    #+#             */
/*   Updated: 2024/11/19 17:22:06 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_builtin_command(t_data *data)
{

	if (ft_strcmp(data->cmd[data->i]->cmd, "exit") == 0)
		data->builtin_cmd = 1;
	else if (ft_strcmp(data->cmd[data->i]->cmd, "export") == 0)
		data->builtin_cmd = 1;
	else if (ft_strcmp(data->cmd[data->i]->cmd, "unset") == 0)
		data->builtin_cmd = 1;
	else if (ft_strcmp(data->cmd[data->i]->cmd, "cd") == 0)
		data->builtin_cmd = 1;
	else if (ft_strcmp(data->cmd[data->i]->cmd, "env") == 0)
	{
		data->builtin_cmd = 1;
		data->display_builtin_cmd = 1;
	}
	else if (ft_strcmp(data->cmd[data->i]->cmd, "pwd") == 0)
	{
		data->builtin_cmd = 1;
		data->display_builtin_cmd = 1;
	}
	else if (ft_strcmp(data->cmd[data->i]->cmd, "echo") == 0)
	{
		data->builtin_cmd = 1;
		data->display_builtin_cmd = 1;
	}

}

void	redirection_builtin_command(t_data *data)
{
	if (data->cmd[data->i]->pos_here_doc > data->cmd[data->i]->pos_input)
		ft_redirection_here_doc(data);
	else if (data->cmd[data->i]->pos_here_doc < data->cmd[data->i]->pos_input)
		ft_redirection_in(data);
	if (data->cmd[data->i]->output_file != NULL || data->cmd[data->i]->append_file != NULL)
		ft_redirection_out_cmd(data);
}

void	execute_builtin_command(t_data *data)
{
	char	**args;
	
	if (data->cmd[data->i] && data->cmd[data->i]->cmd) 
	{
		if (data->cmd[data->i]->cmd == NULL)
		{
			data->back_in_main = 1;
			data->exit_status = 0;
			return ;
		}
		args = data->cmd[data->i]->cmd_arg;
		check_builtin_command(data);
		if (data->nb_pipe == 0 && data->builtin_cmd == 1)
			redirection_builtin_command(data);
		if (ft_strcmp(data->cmd[data->i]->cmd, "echo") == 0)
			echo(data);
		else if (ft_strcmp(data->cmd[data->i]->cmd, "exit") == 0)
			exit_total(data);
		else if (ft_strcmp(args[0], "export") == 0)
			export_var(data, args[1]);
		else if (ft_strcmp(args[0], "unset") == 0)
			unset_var(data, args[1]); // Удаляем переменную
		else if (ft_strcmp(args[0], "env") == 0)
			print_env(data);
		else if (ft_strcmp(args[0], "pwd") == 0)
			pwd(data);
	}
}
