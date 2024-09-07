/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 04:50:05 by mmychaly          #+#    #+#             */
/*   Updated: 2024/09/07 05:44:50 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_accessibility(t_data *data, int row, int col)
{
	if (row < 0 || col < 0 || row >= data->map_height || col >= data->map_width)
		return ;
	if (data->map[row][col] == 'x'
	|| (data->map[row][col] != '0' && data->map[row][col] != 'E'
	&& data->map[row][col] != 'P' && data->map[row][col] != 'C'))
		return ;
	if (data->map[row][col] == 'C')
		data->checker.coin--;
	if (data->map[row][col] == 'E')
		data->checker.exit--;
	data->map[row][col] = 'x';
	check_accessibility(data, row - 1, col);
	check_accessibility(data, row + 1, col);
	check_accessibility(data, row, col - 1);
	check_accessibility(data, row, col + 1);
}

void	check_close_map(t_data *data)
{
	int	i;
	int	i_2;

	i = 0;
	while (i < data->map_height)
	{
		i_2 = 0;
		if (i == 0 || i == (data->map_height - 1))
		{
			while (data->map[i][i_2] != '\n' && data->map[i][i_2] != '\0')
			{
				if (data->map[i][i_2] != '1')
					mixt_error(data, 'O');
				i_2++;
			}
		}
		else
			check_close_map_utils(data, i);
		i++;
	}
}

void	check_symb(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->map_height)
	{
		check_symb_utils(data, i);
		i++;
	}
	if (data->coin_counter < 1)
		mixt_error(data, 'C');
	if (data->departure_counter != 1)
		mixt_error(data, 'D');
	if (data->exit_counter != 1)
		mixt_error(data, 'E');
}

void	check_map(t_data *data)
{
	if (data->map_height == data->map_width)
		mixt_error(data, 'F');
	check_symb(data);
	check_close_map(data);
	data->checker.coin = data->coin_counter;
	data->checker.exit = data->exit_counter;
	check_accessibility(data, data->player.y, data->player.x);
	if (data->checker.coin > 0)
		mixt_error(data, 'c');
	if (data->checker.exit > 0)
		mixt_error(data, 'e');
	free_strs(data);
}
