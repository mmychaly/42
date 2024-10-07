/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 04:06:07 by mmychaly          #+#    #+#             */
/*   Updated: 2024/10/05 05:50:35 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**check_strs(char **strs_argv)
{
	int nbr_strs;
	int i;
	char **strs;
	char *option;
	char *temp;
	
	nbr_strs = 0;
	i = 1;
	while (strs_argv[nbr_strs] != NULL)
		nbr_strs++;
	if (nbr_strs == 2)
		return (strs_argv);
//	printf("ici\n");
	if (strs_argv[1][0] != '\'' || strs_argv[nbr_strs - 1][ft_strlen(strs_argv[nbr_strs - 1]) - 1] != '\'')
		return (ft_free_strs(strs_argv), NULL);
//	printf("ici2\n");
	option = ft_strdup(strs_argv[i] + 1);
	if (option == NULL)
		return (ft_free_strs(strs_argv),NULL);
	i = 2;
	while (strs_argv[i] != NULL)
	{
		temp = ft_strjoin(option, strs_argv[i]);
		if (temp == NULL)
			return (free(option), ft_free_strs(strs_argv), NULL);
		free(option);
		option = temp;
		i++;
	}
	option[ft_strlen(option) - 1] = '\0';
	temp = ft_strdup(strs_argv[0]);
	if (temp == NULL)
		return (free(temp), ft_free_strs(strs_argv), NULL);
	ft_free_strs(strs_argv);
	strs = malloc(sizeof(char *) * 3);
	if (strs == NULL)
		return (free(temp), free(option), NULL);
	strs[0] = temp;
	printf("strs[0] == %s\n", strs[0]);
	strs[1] = option;
	printf("strs[1] == %s\n", strs[1]);
	strs[2] = NULL;
	printf("strs[2] == %s\n", strs[2]);
	return (strs);
}
