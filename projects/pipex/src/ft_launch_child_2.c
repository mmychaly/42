/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_child_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 02:32:53 by mmychaly          #+#    #+#             */
/*   Updated: 2024/08/13 22:10:57 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_redirection_out(char *argv, int pipefd)
{
	int	fd_out;

	fd_out = open(argv, O_WRONLY | O_TRUNC | O_CREAT, 0644); //Открываем файлы в который выведем конечный результат, если он не создан то создаем
	if (fd_out == -1)
	{
		perror("open outfile");
		close(pipefd);
		exit (1);
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1) //Перенаправлем канал выхода на наш файл выхода,теперь результат работы команы выведется не в терминал а в файл
	{
		perror("dup2 fd_out");
		close(pipefd); //Еслине получилось закрываем пайп и дескиптор файла
		close(fd_out);
		exit (EXIT_FAILURE);
	}
	close(fd_out); //Закрываем файловый дескриптор так как мы уже перенаправили выход и стандартный выход будет работать как этот файловый дескриптор
	if (dup2(pipefd, STDIN_FILENO) == -1) //Перенаправляем стандартный вход на канал чтения из пайпа, теперь при запуске команды она будет брать информацию не из терминала а из буффера пайпа
	{
		perror("dup2 pipefd[0]");
		close(pipefd); //Закрываем канал в случае ошибки
		exit (EXIT_FAILURE);
	}
	close(pipefd); //Закрываем канал так как все уже пренаправили
}

void	ft_launch_child_2(char **argv, char *envp[], int pipefd[2]) // Функция для чтения из пайпа , передачи данных во вторую команды и вывода результата второй команды в файл выхода.
{
	char	**strs_argv;
	char	*cmd;

	close(pipefd[1]);//Закрываем канал записи так как мы его не используем
	ft_redirection_out(argv[4], pipefd[0]);//Пернаправлем файловые дескрипторы
	strs_argv = ft_split(argv[3], ' ');//Все тоже самое чтои в прошлой функции
	if (strs_argv == NULL)
		ft_error_exit(1);
	if (access(strs_argv[0], F_OK | X_OK) == 0)
	{
		cmd = ft_strdup(strs_argv[0]);
		if (cmd == NULL)
			free_fault_cmd(strs_argv);
	}
	else
		cmd = ft_envp_cherch(strs_argv[0], envp);
	if (cmd == NULL)
	{
		ft_free_strs(strs_argv);
		exit(127);
	}
	if (execve(cmd, strs_argv, envp) == -1)
		free_fault_execve(strs_argv, cmd);
}
