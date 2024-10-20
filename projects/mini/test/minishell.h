#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>



typedef struct s_cmd
{
    char *input_file;     // Для "<"
    int pos_input;        // Позиция для приоритета входного редиректа
    char *here_doc_file;  // Для "<<"
    int pos_here_doc;     // Позиция для приоритета here_doc
    char *cmd;            // Основная команда (например, "echo")
    char *cmd_arg;        // Аргументы команды (например, "hello world")
    char *output_file;    // Для ">"
    char *append_file;    // Для ">>"
    int pos_output;       // Позиция для приоритета вывода
    int pos_append;       // Позиция для приоритета append
} t_cmd;

typedef struct s_data
{
    char **envp;      // Переменные окружения
    t_cmd **cmd;      // Массив структур команд
    int nb_pipe;      // Количество пайпов
    int i;            //commande actuel                                                               //add
    int prev_pipe;    // Флаг пайпа для предыдущей команды
    int here_doc_pfd; // Flag pour here doc                                                             //add
} t_data;

/*typedef struct s_command
{
	char **envp;
	char **argv;       
	char *input_file;  // Файл для оператора <
	char *here_doc_file;      // Флаг для оператора <<
	char *output_file; // Файл для операторов > и >>
	char *append_file;        // Флаг для оператора >>
	int is_pipe;       // Флаг для пайпа

	int prev_pipe; //Нужно с смого начала инициализировать 0 потом не трогать 
}			t_command;*/

void		parse_pipeline(t_data *command, char *input);
// void	execute_pipeline(char ***commands, char **envp);
//void		free_parsed_commands(t_data **commands);
char		*find_command(char *cmd, char **envp);
void		free_split(char **args);
void		error_exit(const char *message);
char		**ft_split_quotes(const char *input);


int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
int		ft_strlen(const char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strdup(const char *s);
char	*ft_envp_cherch(char *cmd, char **envp);
char	*ft_creat_path(char **strs, char *cmd);
void	ft_add_cmd(char **strs, char *cmd);
void	ft_add_symb(char **strs);

void		choice_execution(t_data *data);
void		execution_cmd(t_data *data);
void		ft_launch_cmd(t_data *data, int pipefd[2]);
void	    wait_processes(t_data *data);
void		ft_launch_here_doc(t_data *data);
void		execution_here_doc(t_data *data);

void	redirection_input(t_data *data, int pipefd[2]);
void	redirection_output(t_data *data, int pipefd[2]);

void	ft_redirection_out_cmd(t_data *data, int flag_pipe);
void    ft_redirection_in(t_data *data,int pipefd[2]);
void	ft_redirection_here_doc(t_data *data, int pipefd[2]);
void	ft_redirection_pipe(t_data *data, int pipefd[2]);

void		free_fault_execve(char **strs, char *cmd, int flag);
void		ft_free_strs(char **strs);
void		ft_error_exit(int nb);
void		free_pipe(int fd);
void		error_split(int flag);
void		error_empty_cmd(int flag);
void		error_cmd(int flag);
void		free_error_cmd(char **strs_argv, int flag);
void		error_open_outfile(int flag);
void		error_dup2_out(int prev_pipe, int flag);

char		*get_next_line(int fd);

#endif
