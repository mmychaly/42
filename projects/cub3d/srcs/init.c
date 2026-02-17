/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 03:43:21 by mmychaly          #+#    #+#             */
/*   Updated: 2025/02/15 03:43:22 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_data(t_data *data, char *map_path)
{
	ft_memset(data, 0, sizeof(t_data));
	data->f = -1;
	data->c = -1;
	parse_cub_file(data, map_path);
}
