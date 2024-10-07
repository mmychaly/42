/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_child_other.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 02:03:48 by mmychaly          #+#    #+#             */
/*   Updated: 2024/10/02 06:38:49 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_redirection_between(int pipefd, int prev_pipe)
{
	if (dup2(prev_pipe, STDIN_FILENO) == -1) //Перенаправляем стандарный вход на файл,теперь когда команда запросит данные она возьмет их из файла а не из терминала
	{
		perror("dup2 pipefd[0]");
		close(prev_pipe);
		close(pipefd); //Закрываем пайп 
		exit (EXIT_FAILURE);
	}
	close(prev_pipe);
	if (dup2(pipefd, STDOUT_FILENO) == -1) //Перенаправляем стандартный выход на конец записи,теперь после выполнения комманды команда выведет информацию не в терминал а в конец записи пайпа, который сохранит информацию в буффере
	{
		perror("dup2 pipefd[1]");
		close(pipefd); //Закрываем пайп 
		exit (EXIT_FAILURE);
	}
	close(pipefd);  //Закрываем пайп , так как мы уже перенаправили канал вывода на пайп
}

void	ft_launch_other(int i, char **argv, char *envp[], int pipefd[2], int prev_pipe) //Функция записи в пайп
{
	char	**strs_argv;
	char	*cmd;

	printf("in ft_launch_other // i = %i \n", i);
	close(pipefd[0]);
	ft_redirection_between(pipefd[1], prev_pipe); //Функция переадресации стандарных входа и выхода
	strs_argv = ft_split(argv[i], ' '); //Разделяем аргумент командной строки в которой указывалось имя команды и аргумент для нее
	if (strs_argv == NULL)
		ft_error_exit(1);
	if (access(strs_argv[0], F_OK | X_OK) == 0) //Провреяем перую строку аргумента является ли она полным путем к бинарному файлу , существует ли такой и можно ли его исполнить
	{
		cmd = ft_strdup(strs_argv[0]); //Если да то значит нам не нужно искать путь и мы просто создаем отдельную строку под нее
		if (cmd == NULL)
			free_fault_cmd(strs_argv);
	}
	else
		cmd = ft_envp_cherch(strs_argv[0], envp); //Если нет то запускаем функцию которая найдет путь к бинарному файлу команды
	if (cmd == NULL)
	{
		ft_free_strs(strs_argv); //Если мы не нашли путь то высвобождаем массив и выходим по ошибке 127
		exit(127);
	}
	if (execve(cmd, strs_argv, envp) == -1) //Функци запускает программу из нашей программы, при этом закрывает дочерний процесс.
		free_fault_execve(strs_argv, cmd);//Если команда не запустилась высвобождаем все.
}
