/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemii <artemii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 02:03:14 by artemii           #+#    #+#             */
/*   Updated: 2025/02/21 00:36:47 by artemii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static void	assign_texture(t_data *data, char **split, char **texture_field,
		char *dup_err)
{
	if (*texture_field != NULL)
		error_with_exit(data, dup_err, NULL, split);
	if (!split[1] || split[2])
		error_with_exit(data, "Textures: wrong arguments", NULL, split);
	*texture_field = ft_strdup(split[1]);
	check_texture_file(*texture_field, data, split);
}

void	parse_texture_line(t_data *data, char **split)
{
	if (ft_strncmp(split[0], "NO", 3) == 0)
		assign_texture(data, split, &data->no, "Duplicate NO texture");
	else if (ft_strncmp(split[0], "SO", 3) == 0)
		assign_texture(data, split, &data->so, "Duplicate SO texture");
	else if (ft_strncmp(split[0], "WE", 3) == 0)
		assign_texture(data, split, &data->we, "Duplicate WE texture");
	else if (ft_strncmp(split[0], "EA", 3) == 0)
		assign_texture(data, split, &data->ea, "Duplicate EA texture");
	else
		error_with_exit(data, "Invalid texture identifier", NULL, split);
}

static void	parse_color_line(t_data *data, char **split, char id)
{
	char	*joined;
	char	*color_str;

	joined = join_tokens(split, 1);
	color_str = remove_all_spaces(joined);
	free(joined);
	if (id == 'F')
	{
		if (data->f != -1)
			error_with_exit(data, "Duplicate floor color", color_str, split);
		data->f = define_colors(color_str);
		if (data->f == -1)
			error_with_exit(data, "Invalid floor color", color_str, split);
	}
	else if (id == 'C')
	{
		if (data->c != -1)
			error_with_exit(data, "Duplicate ceiling color", color_str, split);
		data->c = define_colors(color_str);
		if (data->c == -1)
			error_with_exit(data, "Invalid ceiling color", color_str, split);
	}
	else
		error_with_exit(data, "Invalid color identifier", color_str, split);
	free(color_str);
}

void	parse_single_line(t_data *data, char *line)
{
	char	**split;

	if (!line || !(*line))
		return ;
	split = ft_split(line, ' ');
	if (!split || !split[0])
	{
		free_strs(split);
		return ;
	}
	if (ft_strncmp(split[0], "NO", 3) == 0 || ft_strncmp(split[0], "SO", 3) == 0
		|| ft_strncmp(split[0], "WE", 3) == 0 || ft_strncmp(split[0], "EA",
			3) == 0)
		parse_texture_line(data, split);
	else if (ft_strncmp(split[0], "F", 2) == 0)
		parse_color_line(data, split, 'F');
	else if (ft_strncmp(split[0], "C", 2) == 0)
		parse_color_line(data, split, 'C');
	else
		error_with_exit(data, "Invalid identifier in header", NULL, split);
	free_strs(split);
}

void	parse_textures_and_colors(t_data *data, int fd)
{
	int	end_of_header;

	end_of_header = 0;
	while (!end_of_header)
	{
		data->line = get_next_line(fd);
		if (!data->line)
			error_with_exit(data, "Empty .cub file", NULL, NULL);
		remove_newline(data->line);
		parse_single_line(data, data->line);
		free(data->line);
		data->line = NULL;
		end_of_header = is_all_textures_and_colors_set(data);
		if (end_of_header)
			break ;
	}
}
