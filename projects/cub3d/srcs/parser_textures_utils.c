/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_textures_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemii <artemii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 02:04:02 by artemii           #+#    #+#             */
/*   Updated: 2025/02/13 02:13:20 by artemii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

char	*remove_all_spaces(const char *s)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = malloc(ft_strlen(s) + 1);
	if (!res)
		return (NULL);
	while (s[i])
	{
		if (s[i] != ' ')
			res[j++] = s[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}

int	is_all_textures_and_colors_set(t_data *data)
{
	if (!data->no || !data->so || !data->we || !data->ea)
		return (0);
	if (data->f < 0 || data->c < 0)
		return (0);
	return (1);
}

char	*join_tokens(char **tokens, int start_index)
{
	char	*result;
	char	*tmp;
	int		i;

	result = ft_strdup("");
	i = start_index;
	while (tokens[i])
	{
		tmp = ft_strjoin(result, tokens[i]);
		free(result);
		result = tmp;
		i++;
	}
	return (result);
}

void	check_texture_file(char *path, t_data *data, char **split)
{
	int	len;

	if (!path)
		error_with_exit(data, "Texture path is NULL", NULL, NULL);
	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
		error_with_exit(data, "Invalid texture file extension (should be .xpm)",
			NULL, split);
	if (access(path, R_OK) != 0)
		error_with_exit(data, "Texture not exist/don't have permiss", NULL,
			split);
}
