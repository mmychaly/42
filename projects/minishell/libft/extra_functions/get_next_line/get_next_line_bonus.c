/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakharo <azakharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 14:04:06 by azakharo          #+#    #+#             */
/*   Updated: 2024/07/06 15:56:14 by azakharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*append_buffer_to_stored(char *stored, char *buffer)
{
	char	*temp;

	if (!stored)
		stored = ft_strdup(buffer);
	else
	{
		temp = ft_strjoin(stored, buffer);
		free(stored);
		stored = temp;
	}
	return (stored);
}

static char	*get_line(char *stored)
{
	int		i;
	char	*line;

	i = 0;
	if (!stored[i])
		return (NULL);
	while (stored[i] && stored[i] != '\n')
		i++;
	if (stored[i] == '\n')
		line = ft_substr(stored, 0, i + 1);
	else
		line = ft_substr(stored, 0, i);
	return (line);
}

char	*save_remainder(char *stored)
{
	char	*remainder;
	size_t	i;

	i = 0;
	while (stored[i] && stored[i] != '\n')
		i++;
	if (!stored[i] || !stored[i + 1])
	{
		free(stored);
		return (NULL);
	}
	remainder = ft_substr(stored, i + 1, ft_strlen(stored) - i - 1);
	free(stored);
	return (remainder);
}

char	*read_and_store(int fd, char *stored)
{
	ssize_t	bytes_read;
	char	*buffer;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			free(stored);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		stored = append_buffer_to_stored(stored, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (stored);
}

char	*get_next_line(int fd)
{
	static char	*stored[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stored[fd] = read_and_store(fd, stored[fd]);
	if (!stored[fd])
		return (NULL);
	line = get_line(stored[fd]);
	stored[fd] = save_remainder(stored[fd]);
	return (line);
}
/*#include <stdio.h>

int	main(void)
{
	char	*line;
	int		i;
	int		fd1;
	int		fd2;

	fd1 = open("text_1.txt", O_RDONLY);
	fd2 = open("text_2.txt", O_RDONLY);
	i = 0;
	while (i < 3)
	{
		line = get_next_line(fd1);
		printf("line [%02d]: %s", i, line);
		free(line);
		line = get_next_line(fd2);
		printf("line [%02d]: %s", i, line);
		free(line);
		i++;
	}
	close(fd1);
	close(fd2);
	return (0);
}
*/
