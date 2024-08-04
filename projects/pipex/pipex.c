#include "pipex.h"

void ft_execution(char **argv, char *envp[])
{
	int pid_1;
	int	pid_2;
	int pipefd[2];
	int status;

	if (pipe(pipefd) == -1)
		return (perror("pipe"));
	pid_1 = fork();
	if (pid_1 == -1)
		return (perror("pid_1"));
	if(pid_1 == 0)
		ft_launch_child_1(argv, envp, pipefd);
	pid_2 = fork();
	if (pid_2 == -1)
		return (perror("pid_2"));
	if(pid_2 == 0)
		ft_launch_child_2(argv, envp, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid_1, &status, 0);
	waitpid(pid_2, &status, 0);
}

int main(int argc, char **argv, char *envp[])
{
	if (argc == 5)
	{
		if (access(argv[1], F_OK) == -1)
		{
			if (access(argv[4], F_OK) == -1)
				ft_create_empty_file(argv[4]);
			printf("bash: %s: %s\n", argv[1], strerror(errno)); //Переделать под мой ft_printf.
			return (1);
		}
		if ((access(argv[4], F_OK) == -1))
			ft_create_empty_file(argv[4]);
		ft_execution(argv, envp);
	}
	return 0;
}
