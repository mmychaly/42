/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:27:49 by mmychaly          #+#    #+#             */
/*   Updated: 2024/10/04 19:45:55 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_execution(int nbr_cmd, char **argv, char *envp[])
{
	int	pid;
	int	pipefd[2]; //Массив инт для пайпа, 2 канала // 0 для чтения из пайпа 1 для записи в пайп
	int prev_pipe;
	int	status; //Для ослеживания как завершился процесс
	int i;

	i = 2;
	prev_pipe = -1;
	while (i < nbr_cmd + 2 )
	{
		if (i != nbr_cmd + 1 && pipe(pipefd) == -1) //Я буду создавать новый пайп пока не окажусь в последней комаде, для нее не нужен пайп так как использует чтение из прошлого и выводит в файл
			ft_error_exit(1);
		pid = fork();
		if (pid == -1)
			ft_error_exit(1);
		if (pid == 0) //Все тоже самое что и для первого 
		{
			if (i == 2)
				ft_launch_child_1(i, argv, envp, pipefd);
			else if (i == nbr_cmd + 1)
				ft_launch_child_2(i, argv, envp, prev_pipe);
			else
				ft_launch_other(i, argv, envp, pipefd, prev_pipe);
		}
		if (prev_pipe != -1)
			close(prev_pipe);
		if (i != nbr_cmd + 1) // Закрываем конец записи текущего пайпа в родительском процессе
			close(pipefd[1]);
		prev_pipe = pipefd[0];
		if (i == nbr_cmd + 1) //Условие сработает если мы находимся в последнем процессе 
			prev_pipe = pid; // Сохраняем PID последнего процесса, использую prev_pipe так он мне дальше не нужен
		i++;
		printf("pid == %i\n", pid);
	}
	while ((pid = waitpid(-1, &status, 0)) > 0) //параметр -1 указывает на то что мы ждем завершение любого дочернего процесса, что позволяет не указывать на конкретный процесс
	{
		if (pid == prev_pipe) //Мы проерим статус и выйдим из программы когда закончим последний дочерний процесс
		{
			printf("exit prev_pipe == %i\n", prev_pipe);
			if (WIFEXITED(status))
				exit(WEXITSTATUS(status));
			else
				ft_error_exit(1);
		}
	}
}

int	main(int argc, char **argv, char *envp[])
{
	int	nbr_cmd;

	nbr_cmd = argc - 3;
	if (argc >= 5) //Проверяем количество аргументов , все что больше/меньше 5 не корректно //ВОзможно стоило проверить envp на NULL и выйти по ошибке 
		ft_execution(nbr_cmd, argv, envp);
	else
	{
		write(2, "Error: Incorrect number of arguments\n", 37);
		exit (EXIT_FAILURE);
	}
	return (0);
}
