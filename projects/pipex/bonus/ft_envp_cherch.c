/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envp_cherch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 02:22:54 by mmychaly          #+#    #+#             */
/*   Updated: 2024/08/13 21:53:46 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_add_symb(char **strs)
{
	char	*symb;
	char	*strs_mod;
	int		i;

	symb = "/";
	i = 0;
	while (strs[i] != NULL)
	{
		strs_mod = ft_strjoin(strs[i], symb); //С помощью функции добавляем символ в конце строки 
		if (strs_mod == NULL)
		{
			perror("Error in ft_strjoin for ft_add_symb");
			ft_free_strs(strs); //Если что то пошло не так то высвобождаем память из масива строк который станет NULL
			return ;
		}
		free(strs[i]); //Каждый раз перед предаче в строку модифицированно строки высвобождаем память прошло строки (не модифицированной)
		strs[i] = strs_mod;
		i++;
	}
}

void	ft_add_cmd(char **strs, char *cmd)
{
	char	*strs_mod;
	int		i;

	i = 0;
	while (strs[i] != NULL)
	{
		strs_mod = ft_strjoin(strs[i], cmd);
		if (strs_mod == NULL)
		{
			perror("Error in ft_strjoin for ft_add_cmd");
			ft_free_strs(strs);
			return ;
		}
		free(strs[i]);
		strs[i] = strs_mod;
		i++;
	}
}

char	*ft_creat_path(char **strs, char *cmd)
{
	char	*res;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(cmd);
	while (strs[i] != NULL)
	{
		if (access(strs[i], F_OK | X_OK) == 0) //Проходим по каждому пути , если функци подтвердит что файл команды есть в данном пути и что его можно исполнить то мы нашли правильный путь 
			break ;
		i++;
	}
	if (strs[i] == NULL) //Если NULL то значит мы ошиблись в имени команды либо такой команды не существует
	{
		write(2, cmd, len); //Выводим имя команды и ошибку
		write(2, ": command not found\n", 21);
		return (NULL);
	}
	res = ft_strdup(strs[i]); //Если все ок то копируем строку с путем к команде в отдельную строку
	if (res == NULL)
	{
		perror("Error in ft_strdup");
		return (NULL);
	}
	return (res);
}

char	*ft_envp_cherch(char *cmd, char **envp) //Функци для поиска пути к бинарному файлу команды,возвращает строку с путем и именем команды в конце /usr/bin/grep
{
	int		i;
	char	**strs;
	char	*res;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0) //Ищем в окруженнии строку которая начинается на PATH строка со всеми путями 
		i++;
	strs = ft_split(envp[i] + 5, ':'); //Разделяем строку на множество различных подпутей
	if (strs == NULL)
	{
		perror("Error in split");
		return (NULL);
	}
	ft_add_symb(strs); //Функция которая проходит по каждому путю и добавляет знак '/' в конце /usr/bin -> /usr/bin/
	if (strs == NULL)
		return (NULL);
	ft_add_cmd(strs, cmd); //Функция которая добавляет имя команды в конце каждого пути .Команда cat /usr/bin/ -> /usr/bin/cat
	if (strs == NULL)
		return (NULL);
	res = ft_creat_path(strs, cmd);//функция ищет настроящий путь к команде и возвращает его в виде отдельной строки
	ft_free_strs(strs); //Высвобождаем память из массива строк
	if (res == NULL)
		return (NULL);
	return (res); //Возвращаем строку
}
