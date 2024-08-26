#include "checker_bonus.h"

char *ft_separator_line(char  **buffer)
{
	char 	*line_printable = NULL;
	char	*temp = NULL;
	int	i;

	i = 0;
	while ((*buffer)[i] != '\n' && (*buffer)[i] != '\0')
		i++;
	line_printable = ft_substr(*buffer, 0, i + ((*buffer)[i] == '\n'));
    if ((*buffer)[i] == '\n')
        i++;
    temp = ft_strdup(*buffer + i);
    free(*buffer); 
    *buffer = temp;
	temp = NULL;
    return (line_printable);
}

char *get_next_line(int fd)
{
	char	*buffer = NULL;
	static char	*line_buffer = NULL;
	char 	*line_printable = NULL;
	char	*temp = NULL;
	int	res_read;
	
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
        free(line_buffer);
        line_buffer = NULL;
        return (0);
	}
	buffer = malloc (sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	while ((res_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{	
		buffer[res_read] = '\0';
		if (line_buffer == NULL)
		{
			line_buffer = ft_strdup(buffer);
		}
		else
		{
			temp = ft_strjoin(line_buffer, buffer);
			free(line_buffer);
			line_buffer = temp;
			temp = NULL;
		}
		if (ft_strchr(line_buffer, '\n'))
        break;
	}
	free(buffer);
	buffer = NULL;
	if (res_read <= 0 && (!line_buffer || !*line_buffer))
	{
		free(line_buffer);
		line_buffer = NULL;
		free(line_printable);
		line_printable = NULL;
		return (NULL);
	}
	line_printable = ft_separator_line(&line_buffer);
	if (!line_printable || *line_printable == '\0')
	{
		free(line_printable);
		line_printable = NULL;
		return (NULL);
	}
	return (line_printable);
} 

