/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 22:00:23 by mmychaly          #+#    #+#             */
/*   Updated: 2024/09/07 05:45:34 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_close_map_utils(t_data *data, int i)
{
	int	i_2;

	i_2 = 0;
	while (data->map[i][i_2] != '\n')
	{
		if (data->map[i][0] != '1')
			mixt_error(data, 'O');
		if (i_2 == (data->map_width - 1) && data->map[i][i_2] != '1')
			mixt_error(data, 'O');
		i_2++;
	}
}

void	check_symb_utils(t_data *data, int i)
{
	int	i_2;

	i_2 = 0;
	while (data->map[i][i_2] != '\n' && data->map[i][i_2] != '\0')
	{
		if (data->map[i][i_2] == 'C')
			data->coin_counter += 1;
		else if (data->map[i][i_2] == 'E')
			data->exit_counter += 1;
		else if (data->map[i][i_2] == 'P')
		{
			data->departure_counter += 1;
			data->player.y = i;
			data->player.x = i_2;
		}
		else if (data->map[i][i_2] != '1' && data->map[i][i_2] != '0')
			mixt_error(data, 'S');
		i_2++;
	}
}
