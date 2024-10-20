/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 00:06:33 by mmychaly          #+#    #+#             */
/*   Updated: 2024/10/17 02:10:53 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	choice_execution(t_command *commands)
{
	if (commands->is_pipe == 0)
		execution_cmd(commands); //Если нет пайпа исполняем 1 команду
//	else if (commands->is_pipe > 0 && commands->here_doc_file == 0)
//		execution_pipe(commands); //Исполняем команды с пайп но без here doc
/*	else if (commands->is_pipe > 0 && commands->here_doc_file > 0)
		execution_here_doc(commands); //Исполняем команды с here_doc и pipe*/
}
