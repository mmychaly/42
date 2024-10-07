/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 21:17:06 by mmychaly          #+#    #+#             */
/*   Updated: 2024/10/05 05:19:56 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	launch_here_doc(char **argv, int pipefd[2])
{
	char *line;

	line = NULL;
	close(pipefd[0]);
	printf("in launch_here_doc\n"); //Supprimer
	while ((line = get_next_line(0)) != NULL)
	{
		if ((ft_strncmp(argv[2], line, ft_strlen(line) - 1)) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		free(line);
	}
	close(pipefd[1]);
	exit(0);
}