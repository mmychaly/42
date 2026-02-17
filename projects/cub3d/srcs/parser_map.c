/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemii <artemii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 01:48:46 by artemii           #+#    #+#             */
/*   Updated: 2025/02/16 23:44:58 by artemii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

char	**append_line_to_map(t_data *data, char **old_map, char *line)
{
	char	**new_map;
	int		i;

	data->map_height++;
	new_map = (char **)malloc(sizeof(char *) * (data->map_height + 1));
	if (!new_map)
		error_with_exit(data, "malloc failed in append_line_to_map", line,
			NULL);
	new_map[data->map_height] = NULL;
	i = 0;
	while (old_map && old_map[i])
	{
		new_map[i] = old_map[i];
		i++;
	}
	new_map[i] = line;
	free(old_map);
	return (new_map);
}

void	handle_line_before_map(t_data *data, char *trimmed, int *map_started)
{
	if (trimmed[0] == '\0')
	{
		free(trimmed);
		free(data->line);
		data->line = NULL;
	}
	else
	{
		*map_started = 1;
		data->map = append_line_to_map(data, data->map, data->line);
		data->line = NULL;
		free(trimmed);
	}
}

void	handle_line_after_map(t_data *data, char *trimmed, int *map_ended)
{
	if (trimmed[0] == '\0')
	{
		*map_ended = 1;
		free(trimmed);
		free(data->line);
		data->line = NULL;
	}
	else
	{
		if (*map_ended)
		{
			free(trimmed);
			free(data->line);
			data->line = NULL;
			error_with_exit(data,
				"Invalid map: non-empty line after empty line", NULL, NULL);
		}
		data->map = append_line_to_map(data, data->map, data->line);
		data->line = NULL;
		free(trimmed);
	}
}

void	calc_map_width(t_data *data)
{
	int	i;
	int	len;

	data->map_width = 0;
	i = 0;
	while (i < data->map_height)
	{
		len = ft_strlen(data->map[i]);
		if (len > data->map_width)
			data->map_width = len;
		i++;
	}
}

void	parse_map_lines(t_data *data, int fd)
{
	char	*trimmed;
	int		map_started;
	int		map_ended;

	map_started = 0;
	map_ended = 0;
	data->map = NULL;
	data->map_height = 0;
	data->line = get_next_line(fd);
	while ((data->line))
	{
		remove_newline(data->line);
		trimmed = ft_strtrim(data->line, " \t\r\n");
		if (!(map_started))
			handle_line_before_map(data, trimmed, &map_started);
		else
			handle_line_after_map(data, trimmed, &map_ended);
		data->line = get_next_line(fd);
	}
	calc_map_width(data);
	if (data->map_height == 0)
		error_with_exit(data, "Map is empty", NULL, NULL);
}
