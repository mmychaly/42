/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:27:49 by mmychaly          #+#    #+#             */
/*   Updated: 2024/09/28 19:12:07 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_execution(int nbr_cmd, char **argv, char *envp[])
{
	int	pid_first; //Для первого дочернего процесса
	int	pid_last; //Для второго дочернего процесса
	int pid_other;
	int	pipefd[2]; //Массив инт для пайпа, 2 канала // 0 для чтения из пайпа 1 для записи в пайп
	int	status; //Для ослеживания как завершился процесс
	int i;

	i = 2;
	if (pipe(pipefd) == -1) //Создаем пайп
		ft_error_exit(1);
	pid_first = fork(); //Создаем первый дочерний процесс
	if (pid_first == -1)
		ft_error_exit(1);
	if (pid_first == 0) //Для дочернего процесса pid_first == 0 для родительского pid_first == pid дочернего процесса, только дочерний процесс сможет пройти в иф по этому условию 
		ft_launch_child_1(i++, argv, envp, pipefd); //Запускаем основную функцию для дочернего процесса
	while (nbr_cmd > 0)
	{
		pid_other = fork;
		if (pid_other == -1)
			ft_error_exit(1);
		if (pid_other == 0) //Все тоже самое что и для первого 
		ft_launch_child_other(i++, argv, envp, pipefd);
	}
	pid_last = fork(); //Создаем второй дочерний процесс
	if (pid_last == -1)
		ft_error_exit(1);
	if (pid_last == 0) //Все тоже самое что и для первого 
		ft_launch_child_2(i++, argv, envp, pipefd);
	close(pipefd[0]); //Закрываем каналы пайпа в родительском процессе так как мы их здесь не используем 
	close(pipefd[1]); //Закрываем второй
	waitpid(pid_first, &status, 0); //Родтельский процесс будет продолжит исполнять инструкции только после завершения первого дочеренго процесса
	waitpid(pid_other, &status, 0); 
	waitpid(pid_last, &status, 0); //Так же ждем пока не завершиться второй дочерний процесс
	if (WIFEXITED(status)) //Принимаем статус , если возвращает 0 то завершили процесс корректно через exit //Обращаем внимание на статус последнего процесса
		exit(WEXITSTATUS(status)); //Выводим значение с которым закрыли процесс
	else
		ft_error_exit(1); //Вышли из процесса не корректно 
}

int	main(int argc, char **argv, char *envp[])
{
	int	nbr_cmd;

	nbr_cmd = argc - 5;
	if (argc == 5) //Проверяем количество аргументов , все что больше/меньше 5 не корректно //ВОзможно стоило проверить envp на NULL и выйти по ошибке 
		ft_execution(nbr_cmd, argv, envp);
	else
	{
		write(2, "Error: Incorrect number of arguments\n", 37);
		exit (EXIT_FAILURE);
	}
	return (0);
}
