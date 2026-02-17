/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemii <artemii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 01:46:49 by artemii           #+#    #+#             */
/*   Updated: 2025/02/25 01:26:47 by artemii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static int	has_cub_extension(const char *filename)
{
	int	len;

	if (!filename)
		return (0);
	len = 0;
	while (filename[len])
		len++;
	if (len < 4)
		return (0);
	return (!((filename[len - 4] != '.') || (filename[len - 3] != 'c')
			|| (filename[len - 2] != 'u') || (filename[len - 1] != 'b')));
}

void	parse_cub_file(t_data *data, char *map_path)
{
	int	fd;

	if (!has_cub_extension(map_path))
		error_with_exit(data, "Wrong file extension (not .cub)", NULL, NULL);
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		error_with_exit(data, "Failed to open map file", NULL, NULL);
	data->fd = fd;
	parse_textures_and_colors(data, fd);
	parse_map_lines(data, fd);
	close(fd);
	pad_map(data);
	if (check_map_validity(data) < 0)
		error_with_exit(data, "Invalid map", NULL, NULL);
	if (check_map_closure(data) < 0 || check_map_closure_flood(data) < 0)
		error_with_exit(data, "Invalid map closure", NULL, NULL);
}
