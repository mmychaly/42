/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemii <artemii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 00:47:10 by artemii           #+#    #+#             */
/*   Updated: 2024/11/28 15:17:09 by artemii          ###   ########.fr       */
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

void	update_redirection(char **target_file, char ***file_array, char *token)
{
	if (*target_file)
		free(*target_file);
	*target_file = ft_strdup(token);
	*file_array = realloc_array(*file_array, ft_strdup(token));
}

void	handle_redirection(t_cmd *cmd, char **tokens, int *i,
		int *redir_position)
{
	if (ft_strcmp(tokens[*i], "<") == 0)
	{
		(*i)++;
		cmd->pos_input = (*redir_position)++;
		update_redirection(&cmd->input_file, &cmd->input_files, tokens[*i]);
	}
	else if (ft_strcmp(tokens[*i], ">") == 0)
	{
		(*i)++;
		cmd->pos_output = (*redir_position)++;
		update_redirection(&cmd->output_file, &cmd->output_files, tokens[*i]);
	}
	else if (ft_strcmp(tokens[*i], ">>") == 0)
	{
		(*i)++;
		cmd->pos_append = (*redir_position)++;
		update_redirection(&cmd->append_file, &cmd->append_files, tokens[*i]);
	}
	else if (ft_strcmp(tokens[*i], "<<") == 0)
	{
		(*i)++;
		cmd->pos_here_doc = (*redir_position)++;
		update_redirection(&cmd->here_doc_file, &cmd->here_doc_files,
			tokens[(*i)]);
	}
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
