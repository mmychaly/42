/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_here_doc_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 21:17:06 by mmychaly          #+#    #+#             */
/*   Updated: 2024/10/13 15:49:27 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	launch_here_doc(t_data *data)
{
	char	*line;
	int		pipefd[2];

	line = NULL;
	if (pipe(pipefd) == -1)
		ft_error_exit(1);
	data->prev_pipe = pipefd[0];
	line = get_next_line(0);
	while (line != NULL)
	{
		if ((ft_strncmp(data->argv[2], line, ft_strlen(line) - 1)) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	close(pipefd[1]);
}
