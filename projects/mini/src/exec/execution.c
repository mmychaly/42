/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 00:06:33 by mmychaly          #+#    #+#             */
/*   Updated: 2024/11/05 20:48:31 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	choice_execution(t_data *data)
{
	if (g_pid == -50) //Если прошел сигнал sigint с выводом новой строки то перед вызовом новой команды обнавлем статус выхода
	{
		data->exit_status = 130;
		g_pid = -1;
	}
	execution_cmd(data);
}