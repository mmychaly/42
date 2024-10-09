/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 17:02:05 by mmychaly          #+#    #+#             */
/*   Updated: 2024/10/04 22:28:31 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_separator_line(char **buffer)
{
	char	*line_printable;
	int		i;

	line_printable = NULL;
	i = 0;
	while ((*buffer)[i] != '\n' && (*buffer)[i] != '\0')
		i++;
	line_printable = ft_substr(*buffer, 0, i + ((*buffer)[i] == '\n'));
	if (!line_printable)
		return (NULL);
	return (line_printable);
}

char	*ft_next_string(char **buffer)
{
	char	*new_buffer;
	int		i;

	i = 0;
	while ((*buffer)[i] != '\n' && (*buffer)[i] != '\0')
		i++;
	if ((*buffer)[i] == '\n')
		i++;
	else
	{
		new_buffer = NULL;
		return (free_error(buffer));
	}
	if ((*buffer)[i] == '\0')
		return (free_error(buffer));
	new_buffer = ft_strdup(*buffer + i);
	free(*buffer);
	if (!new_buffer)
		return (NULL);
	return (new_buffer);
}

char	*ft_read_utils(char **line_buffer, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(*line_buffer, buffer);
	if (!temp)
	{
		free(buffer);
		return (free_error(line_buffer));
	}
	free(*line_buffer);
	*line_buffer = temp;
	temp = NULL;
	return (*line_buffer);
}

char	*ft_read_fd(int fd, char **line_buffer, char *buffer)
{
	int		res_read;

	while (1)
	{
		res_read = read(fd, buffer, BUFFER_SIZE);
		if (res_read <= 0)
			break ;
		buffer[res_read] = '\0';
		if (*line_buffer == NULL)
		{
			*line_buffer = ft_strdup(buffer);
			if (*line_buffer == NULL)
				return (free_error(&buffer));
		}
		else
			if (ft_read_utils(line_buffer, buffer) == NULL)
				return (NULL);
		if (ft_strchr(*line_buffer, '\n'))
			break ;
	}
	free(buffer);
	if (res_read < 0)
		return (free(*line_buffer), NULL);
	return (*line_buffer);
}

char	*get_next_line(int fd)
{
	static char	*line_buffer;
	char		*line_printable;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free_error(&line_buffer));
	buffer = malloc (sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (free_error(&line_buffer));
	buffer[0] = '\0';
	line_buffer = ft_read_fd(fd, &line_buffer, buffer);
	if (line_buffer == NULL)
		return (NULL);
	line_printable = ft_separator_line(&line_buffer);
	if (!line_printable)
		return (free_error(&line_buffer));
	line_buffer = ft_next_string(&line_buffer);
	return (line_printable);
}
