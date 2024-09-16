/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 17:02:05 by mmychaly          #+#    #+#             */
/*   Updated: 2024/09/11 04:54:50 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_separator_line(char **buffer)
{
	char	*line_printable;
	char	*temp;
	int		i;

	line_printable = NULL;
	temp = NULL;
	i = 0;
	while ((*buffer)[i] != '\n' && (*buffer)[i] != '\0')
		i++;
	line_printable = ft_substr(*buffer, 0, i + ((*buffer)[i] == '\n'));
	if ((*buffer)[i] == '\n')
		i++;
	temp = ft_strdup(*buffer + i);
	free(*buffer);
	*buffer = temp;
	return (line_printable);
}

char	*ft_read_fd(int fd, char **line_buffer, char *buffer)
{
	char	*temp;
	int		res_read;

	while (1)
	{
		res_read = read(fd, buffer, BUFFER_SIZE);
		if (res_read == 0)
			break ;
		buffer[res_read] = '\0';
		if (*line_buffer == NULL)
			*line_buffer = ft_strdup(buffer);
		else
		{
			temp = ft_strjoin(*line_buffer, buffer);
			free(*line_buffer);
			*line_buffer = temp;
		}
		if (ft_strchr(*line_buffer, '\n'))
			break ;
	}
	free(buffer);
	if (res_read <= 0 && (*line_buffer == NULL || (*line_buffer)[0] == '\0'))
		return (free(*line_buffer), NULL);
	return (*line_buffer);
}

char	*get_next_line(int fd)
{
	static char	*line_buffer;
	char		*line_printable;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(line_buffer);
		line_buffer = NULL;
		return (NULL);
	}
	buffer = malloc (sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	line_buffer = ft_read_fd(fd, &line_buffer, buffer);
	if (line_buffer == NULL)
		return (NULL);
	line_printable = ft_separator_line(&line_buffer);
	return (line_printable);
}
