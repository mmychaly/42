/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:52:20 by davli             #+#    #+#             */
/*   Updated: 2024/05/30 12:05:52 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

char	*ft_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

char	*ft_update(char *storage)
{
	char	*new_storage;
	char	*ptr;
	int		len;

	ptr = ft_strchr(storage, '\n');
	if (!ptr)
	{
		new_storage = NULL;
		return (ft_free(&storage));
	}
	else
		len = (ptr - storage) + 1;
	if (!storage[len])
		return (ft_free(&storage));
	new_storage = ft_substr(storage, len, ft_strlen(storage) - len);
	ft_free(&storage);
	if (!new_storage)
		return (NULL);
	return (new_storage);
}

char	*new_line(char *storage)
{
	char	*line;
	char	*ptr;
	int		len;

	ptr = ft_strchr(storage, '\n');
	if (!ptr)
		len = ft_strlen(storage);
	else
		len = (ptr - storage) + 1;
	line = ft_substr(storage, 0, len);
	if (!line)
		return (NULL);
	return (line);
}

char	*readbuf(int fd, char *storage)
{
	int		rid;
	char	*buffer;

	rid = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_free(&storage));
	buffer[0] = '\0';
	while (rid > 0 && !ft_strchr(buffer, '\n'))
	{
		rid = read (fd, buffer, BUFFER_SIZE);
		if (rid > 0)
		{
			buffer[rid] = '\0';
			storage = ft_strjoin(storage, buffer);
		}
	}
	free(buffer);
	if (rid == -1)
		return (ft_free(&storage));
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*storage[1024];
	char		*line;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	if (fd < 0)
		return (NULL);
	storage[fd] = readbuf (fd, storage[fd]);
	if (storage[fd] == NULL)
		return (NULL);
	line = new_line(storage[fd]);
	if (line == NULL)
		return (ft_free(&storage[fd]));
	storage[fd] = ft_update(storage[fd]);
	return (line);
}
/*
int	main(int argc, char **argv)
{
	int		fd1;
	int		fd2;
	char	*line;
	int		j = 0;

	if (argc < 3)
	{
		printf("Not enough arguments..");
		return (0);
	}
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[2], O_RDONLY);
	while (j < 20) // modifier ici
	{
		line = get_next_line(fd1);
		printf("%s", line);
		line = get_next_line(fd2);
		printf("%s", line);
		free(line);
		j++;
	}
	close(fd1);
	close(fd2);

	return (0);
}
*/
