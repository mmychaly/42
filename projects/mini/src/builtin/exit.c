/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:   ) //Для exit
	{ :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:27:51 by mmychaly          #+#    #+#             */
/*   Updated: 2024/11/11 04:32:33 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_exit_total(t_data *data)
{
	int nbr_args;
	int	exit_status;


	nbr_args = 0;
	exit_status = data->exit_status;
	if (ft_strcmp(data->cmd[0]->cmd, "exit") == 0 && data->nb_pipe == 0)
	{
		while (data->cmd[0]->cmd_arg[nbr_args] != NULL)
			nbr_args++;
		if (nbr_args > 2 && exit_status == 1)
			nbr_args++;
		else
		{
//			write(2, "exit---------------------------\n", 32);
			free_data(data);
//			free(data->user_input);
			rl_clear_history();
			exit (exit_status);
		}
	}
}

void	exit_total(t_data *data)
{
	int	i_2;
	int flag;
	int	status;
	int nbr_args;

	i_2 = 0;
	flag = 0;
	nbr_args = 0;
	status = 0;
	close_input(data);
	close (1);
	while (data->cmd[data->i]->cmd_arg[nbr_args] != NULL)
		nbr_args++;
	if (data->nb_pipe == 0)
		write(2, "exit\n", 5);
	if (data->cmd[data->i]->cmd_arg[1] != NULL)
	{
		while (data->cmd[data->i]->cmd_arg[1][i_2] != '\0')
		{
			if (flag == 0 && (data->cmd[data->i]->cmd_arg[1][i_2] == '-' || data->cmd[data->i]->cmd_arg[1][i_2] == '+'))
			{
				i_2++;
				flag = 1;
			}
			if (ft_isdigit(data->cmd[data->i]->cmd_arg[1][i_2]) == 0)
			{
				write(2, "exit: numeric argument required\n", 32);
				free_data(data);
				rl_clear_history();
				exit(2);
			}
			i_2++;
		}
		if (nbr_args > 2)
		{
			write(2, "exit: too many arguments\n", 25);
			free_data(data);
			rl_clear_history();
			if (data->nb_pipe == 0)
			{
				data->exit_total = 1;//Pour pouvoir sortir dans main sans commancer 
				data->exit_status = 1;
				return ;
			}
			else
				exit (1) ;
		}
		status = ft_atoi(data->cmd[data->i]->cmd_arg[1]);
		if (status < 0 || status > 255)
			status = status % 256;
	}
//	free(data->user_input); peut etre ca aussi
	free_data(data);
	rl_clear_history();
	exit(status);
}
