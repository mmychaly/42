/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_flood.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemii <artemii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 01:59:19 by artemii           #+#    #+#             */
/*   Updated: 2025/02/14 00:49:54 by artemii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	**allocate_visited(int height, int width)
{
	int	**visited;
	int	i;
	int	j;

	i = 0;
	visited = malloc(sizeof(int *) * height);
	if (!visited)
		return (NULL);
	while (i < height)
	{
		visited[i] = malloc(sizeof(int) * width);
		if (!visited[i])
		{
			j = 0;
			while (j < i)
				free(visited[j++]);
			free(visited);
			return (NULL);
		}
		memset(visited[i], 0, sizeof(int) * width);
		i++;
	}
	return (visited);
}

void	free_visited(int **visited, int height)
{
	int	i;

	i = 0;
	while (i < height)
		free(visited[i++]);
	free(visited);
}

int	flood_fill(t_data *data, int i, int j, int **visited)
{
	if (i < 0 || j < 0 || i >= data->map_height || j >= data->map_width)
		return (1);
	if (data->map[i][j] == ' ')
		return (1);
	if (data->map[i][j] == '1')
		return (0);
	if (visited[i][j])
		return (0);
	visited[i][j] = 1;
	if (flood_fill(data, i - 1, j, visited))
		return (1);
	if (flood_fill(data, i + 1, j, visited))
		return (1);
	if (flood_fill(data, i, j - 1, visited))
		return (1);
	if (flood_fill(data, i, j + 1, visited))
		return (1);
	return (0);
}

int	check_map_closure_flood(t_data *data)
{
	int	**visited;
	int	start_i;
	int	start_j;

	start_i = (int)data->player.pos_y;
	start_j = (int)data->player.pos_x;
	visited = allocate_visited(data->map_height, data->map_width);
	if (!visited)
		error_with_exit(data, "Memory allocation failed in flood fill", NULL,
			NULL);
	if (flood_fill(data, start_i, start_j, visited))
	{
		free_visited(visited, data->map_height);
		return (error_wo_exit("Flood fill reached border or space"));
	}
	free_visited(visited, data->map_height);
	return (0);
}
