/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemii <artemii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 00:21:14 by artemii           #+#    #+#             */
/*   Updated: 2025/02/21 00:27:40 by artemii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	is_str_numeric(char **s)
{
	int	i;
	int	j;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i][0] == '\0')
			return (0);
		i++;
	}
	i = 0;
	while (s[i])
	{
		j = 0;
		while (s[i][j])
		{
			if (!ft_isdigit(s[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	check_unique_textures(t_data *data)
{
	if (ft_strncmp(data->no, data->so, ft_strlen(data->no) + 1) == 0
		|| ft_strncmp(data->no, data->ea, ft_strlen(data->no) + 1) == 0
		|| ft_strncmp(data->no, data->we, ft_strlen(data->no) + 1) == 0
		|| ft_strncmp(data->so, data->ea, ft_strlen(data->so) + 1) == 0
		|| ft_strncmp(data->so, data->we, ft_strlen(data->so) + 1) == 0
		|| ft_strncmp(data->ea, data->we, ft_strlen(data->ea) + 1) == 0)
		error_with_exit(data, "Duplicate texture", NULL, NULL);
}
