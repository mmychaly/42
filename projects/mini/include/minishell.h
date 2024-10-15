#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_command
{
	char **envp;
	char **argv;       // Массив аргументов команды
	/*Массив для команды  << LIMITER grep ? | cat | wc -l
	argv[0] = << //Мне нужен операнд << что бы я мог 
	разлечить here_doc если его будет больше 1 и он будет дальше первой команды
	argv[1] = LIMITER
	argv[2] = grep ?
	argv[3] = cat
	argv[4] = wc -l
	argv[5] = wc -l 
	*/
	/*Массив для команды  < infile grep ? > outfile
	argv[0] = grep ?
	argv[1] = NULL
	*/
	char *input_file;  // Файл для оператора <
	char *here_doc_file;      // Флаг для оператора <<
	char *output_file; // Файл для операторов > и >>
	char *append_file;        // Флаг для оператора >>
	int is_pipe;       // Флаг для пайпа

	int prev_pipe; //Нужно с смого начала инициализировать 0 потом не трогать 
}			t_command;

t_command	*parse_pipeline(char *input);
// void	execute_pipeline(char ***commands, char **envp);
void		free_parsed_commands(t_command **commands);
t_command	*parse_input(char *input);
char		*find_command(char *cmd, char **envp);
void		free_split(char **args);
void		error_exit(const char *message);
void		launch_here_doc(char **argv, int pipefd[2]);
void		ft_redirection_in(char *input_file);
void		ft_redirection_out_append(char *output_file);
void		ft_redirection_out(char *output_file);

void		choice_execution(t_command *commands);
void		execution_cmd(t_command *commands);
void		ft_launch_cmd(t_command *commands, int pipefd[2]);
void		launch_here_doc(t_command *commands);

void		ft_redirection_out_cmd(t_command *commands, int flag_pipe);
void		ft_redirection_in(t_command *commands);
void		ft_redirection_read_pipe(t_command *commands);

void		free_fault_execve(char **strs, char *cmd, int flag);
void		ft_free_strs(char **strs);
void		ft_error_exit(int nb);
void		free_pipe(int fd);
void		error_split(int flag);
void		error_empty_cmd(void, int flag);
void		error_cmd(int flag);
void		free_error_cmd(char **strs_argv, int flag);
void		error_open_outfile(int pipefd, int flag);
void		error_dup2_out(int prev_pipe, int flag);

char		*get_next_line(int fd);

#endif
