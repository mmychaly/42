/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemii <artemii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 01:54:59 by artemii           #+#    #+#             */
/*   Updated: 2025/02/22 23:26:26 by artemii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	check_cell_closure(t_data *data, int i, int j)
{
	int	di;
	int	dj;
	int	ni;
	int	nj;

	di = -1;
	while (di <= 1)
	{
		dj = -1;
		while (dj <= 1)
		{
			ni = i + di;
			nj = j + dj;
			if (ni < 0 || nj < 0 || ni >= data->map_height
				|| nj >= data->map_width)
				return (error_wo_exit("Map is not closed (border reached)"));
			if (data->map[ni][nj] == ' ' && !((di != 0 && dj != 0)
					&& (data->map[i + di][j] == '1' && data->map[i][j
						+ dj] == '1')))
				return (error_wo_exit("Map is not closed (empty space)"));
			dj++;
		}
		di++;
	}
	return (0);
}

int	check_map_closure(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map_height)
	{
		j = 0;
		while (j < data->map_width)
		{
			if (data->map[i][j] == '0' || data->map[i][j] == 'N'
				|| data->map[i][j] == 'S' || data->map[i][j] == 'E'
				|| data->map[i][j] == 'W')
			{
				if (check_cell_closure(data, i, j) < 0)
					return (-1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	move_pos(t_data *data, int *i, int *j, int *player_count)
{
	data->player.pos_x = *j + 0.5;
	data->player.pos_y = *i + 0.5;
	data->player.direction = data->map[*i][*j];
	*player_count += 1;
}

int	check_map_validity(t_data *data)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = 0;
	while (i < data->map_height)
	{
		j = 0;
		while (data->map[i][j])
		{
			if (!is_valid_map_char(data->map[i][j]))
				return (error_wo_exit("Invalid character in map"));
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'E' || data->map[i][j] == 'W')
				move_pos(data, &i, &j, &player_count);
			j++;
		}
		i++;
	}
	if (player_count == 0)
		return (error_wo_exit("No player start position found"));
	if (player_count > 1)
		return (error_wo_exit("Multiple player start positions"));
	return (0);
}

void	pad_map(t_data *data)
{
	int		i;
	char	*new_line;
	int		j;
	int		len;

	i = 0;
	while (i < data->map_height)
	{
		if ((int)ft_strlen(data->map[i]) < data->map_width)
		{
			len = ft_strlen(data->map[i]);
			new_line = malloc(data->map_width + 1);
			if (!new_line)
				error_with_exit(data, "malloc failed in pad_line", NULL, NULL);
			j = -1;
			while (j++ < len)
				new_line[j] = data->map[i][j];
			while (j < data->map_width)
				new_line[j++] = ' ';
			new_line[j] = '\0';
			free(data->map[i]);
			data->map[i] = new_line;
		}
		i++;
	}
}
