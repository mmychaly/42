/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 17:02:05 by mmychaly          #+#    #+#             */
/*   Updated: 2024/09/21 04:43:23 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (i < (size - 1) && src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = 0;
	}
	i = 0;
	while (src[i] != '\0')
		i++;
	return (i);
}

char	*ft_separator_line(char **buffer)
{
	char	*line_printable;
	char	*temp;
	int		i;

	temp = NULL;
	i = 0;
	while ((*buffer)[i] != '\n' && (*buffer)[i] != '\0')
		i++;
	line_printable = ft_substr(*buffer, 0, i + ((*buffer)[i] == '\n'));
	if (!line_printable)
		return (NULL);
	if ((*buffer)[i] == '\n')
		i++;
	temp = ft_strdup(*buffer + i);
	if (!temp)
		return (free(line_printable), NULL);
	free(*buffer);
	*buffer = temp;
	return (line_printable);
}

char	*ft_read_fd_utils(char *buffer, char **temp)
{
	char	*temp_2;

	if (*temp == NULL)
	{
		*temp = ft_strdup(buffer);
		if (!*temp)
			return (NULL);
	}
	else
	{
		temp_2 = ft_strjoin(*temp, buffer);
		if (!temp_2)
			return (NULL);
		free(*temp);
		*temp = temp_2;
	}
	return (*temp);
}

char	*ft_read_fd(int fd, char *line_buffer, char *buffer)
{
	char	*temp;
	int		res_read;

	temp = NULL;
	if (line_buffer[0] != '\0')
	{
		temp = ft_strdup(line_buffer);
		if (!temp)
			return (NULL);
	}
	while (1)
	{
		res_read = read(fd, buffer, BUFFER_SIZE);
		if (res_read == 0)
			break ;
		buffer[res_read] = '\0';
		temp = ft_read_fd_utils(buffer, &temp);
		if (temp == NULL)
			break ;
		if (ft_strchr(temp, '\n'))
			break ;
	}
	if (res_read <= 0 && (temp == NULL || (temp)[0] == '\0'))
		return (free(temp), NULL);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	line_buffer[BUFFER_SIZE + 1];
	char		*line_printable;
	char		*temp;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		line_buffer[0] = '\0';
		return (NULL);
	}
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	temp = ft_read_fd(fd, line_buffer, buffer);
	free(buffer);
	if (temp == NULL)
		return (NULL);
	line_printable = ft_separator_line(&temp);
	if (line_printable != NULL)
		ft_strlcpy(line_buffer, temp, (ft_strlen(temp) + 1));
	free(temp);
	return (line_printable);
}
