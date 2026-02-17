/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemii <artemii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 03:10:27 by mmychaly          #+#    #+#             */
/*   Updated: 2025/02/21 00:31:17 by artemii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

char	*trim_end_spaces(char *str)
{
	int		end;
	char	*res;

	if (!str)
		return (NULL);
	end = 0;
	while (str[end])
		end++;
	end--;
	while (end >= 0 && str[end] == ' ')
		end--;
	res = ft_substr(str, 0, end + 1);
	return (res);
}

int	define_colors(char *str)
{
	char	**nb;
	int		r;
	int		g;
	int		b;
	int		color;

	if (!str)
		return (-1);
	nb = ft_split(str, ',');
	if (!nb || !nb[0] || !nb[1] || !nb[2] || nb[3] || !is_str_numeric(nb))
	{
		free_strs(nb);
		return (-1);
	}
	r = atoi(nb[0]);
	g = atoi(nb[1]);
	b = atoi(nb[2]);
	free_strs(nb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	color = ((unsigned char)r << 16) | ((unsigned char)g << 8)
		| (unsigned char)b;
	return (color);
}

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W');
}

void	printf_map(t_data *data)
{
	int	i;
	int	i_2;

	i = 0;
	i_2 = 0;
	printf("data.no %s\n", data->no);
	printf("data.so %s\n", data->so);
	printf("data.ea %s\n", data->ea);
	printf("data.we %s\n", data->we);
	printf("data.f %x\n", data->f);
	printf("data.c %x\n", data->c);
	while (i < data->map_height)
	{
		i_2 = 0;
		while (data->map[i][i_2] != '\n' && data->map[i][i_2] != '\0')
		{
			printf("%c", data->map[i][i_2]);
			i_2++;
		}
		printf("\n");
		i++;
	}
}

void	remove_newline(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}
