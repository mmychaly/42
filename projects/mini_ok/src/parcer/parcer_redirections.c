/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemii <artemii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 00:47:10 by artemii           #+#    #+#             */
/*   Updated: 2024/11/26 00:53:44 by artemii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**realloc_array(char **array, char *new_element)
{
	int		size;
	int		i;
	char	**new_array;

	size = 0;
	if (array)
		while (array[size])
			size++;
	new_array = malloc(sizeof(char *) * (size + 2));
	if (!new_array)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < size)
	{
		new_array[i] = array[i];
		i++;
	}
	new_array[size] = new_element;
	new_array[size + 1] = NULL;
	free(array);
	return (new_array);
}

void	handle_redir_file(t_cmd *cmd, char *token, int *redir_position,
		int redir_type)
{
	if (redir_type == 0)
	{
		cmd->input_file = ft_strdup(token);
		cmd->pos_input = (*redir_position)++;
		cmd->input_files = realloc_array(cmd->input_files, ft_strdup(token));
	}
	else if (redir_type == 1)
	{
		cmd->output_file = ft_strdup(token);
		cmd->pos_output = (*redir_position)++;
		cmd->output_files = realloc_array(cmd->output_files, ft_strdup(token));
	}
	else if (redir_type == 2)
	{
		cmd->append_file = ft_strdup(token);
		cmd->pos_append = (*redir_position)++;
		cmd->append_files = realloc_array(cmd->append_files, ft_strdup(token));
	}
	else if (redir_type == 3)
	{
		cmd->here_doc_file = ft_strdup(token);
		cmd->pos_here_doc = (*redir_position)++;
		cmd->here_doc_files = realloc_array(cmd->here_doc_files,
				ft_strdup(token));
	}
}

void	handle_redirection(t_cmd *cmd, char **tokens, int *i,
		int *redir_position)
{
	int	redir_type;

	if (ft_strcmp(tokens[*i], "<") == 0)
		redir_type = 0;
	else if (ft_strcmp(tokens[*i], ">") == 0)
		redir_type = 1;
	else if (ft_strcmp(tokens[*i], ">>") == 0)
		redir_type = 2;
	else if (ft_strcmp(tokens[*i], "<<") == 0)
		redir_type = 3;
	else
		return ;
	(*i)++;
	handle_redir_file(cmd, tokens[*i], redir_position, redir_type);
}

void	handle_command_args(t_cmd *cmd, char **tokens, int *i, int *arg_idx)
{
	int	j;

	j = 0;
	if (cmd->cmd_arg == NULL)
	{
		cmd->cmd_arg = malloc(sizeof(char *) * 100);
		if (!cmd->cmd_arg)
			return ;
		while (j < 100)
		{
			cmd->cmd_arg[j] = NULL;
			j++;
		}
		cmd->cmd = ft_strdup(tokens[*i]);
		if (!cmd->cmd)
		{
			free(cmd->cmd_arg);
			cmd->cmd_arg = NULL;
			return ;
		}
	}
	cmd->cmd_arg[(*arg_idx)++] = ft_strdup(tokens[*i]);
}

void	handle_here_docs(t_cmd *cmd, t_data *data)
{
	int	i;

	if (cmd->here_doc_file == NULL)
		return ;
	i = 0;
	while (cmd->here_doc_files[i] != NULL)
	{
		execution_here_doc(cmd, cmd->here_doc_files[i], data);
		if (data->back_in_main == 1)
			return ;
		i++;
	}
}
