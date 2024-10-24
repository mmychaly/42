#include "minishell.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		len;
	char	*dup;

	i = 0;
	len = 0;
	while (s[len] != '\0')
		len++;
	dup = malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void free_cmd(t_cmd *cmd)
{
	printf("\n\n-----free-----\n");
    if (cmd->cmd)         // Освобождаем команду
	{
		printf("cmd %s\n", cmd->cmd);
        free(cmd->cmd);
	}
    if (cmd->cmd_arg)     // Освобождаем аргумент команды
	{
		printf("cmd->cmd_arg %s\n", cmd->cmd_arg);
        free(cmd->cmd_arg);
	}
    if (cmd->input_file)  // Освобождаем файл для входного редиректа
	{
		printf("cmd->input_file %s\n", cmd->input_file);
        free(cmd->input_file);
	}
    if (cmd->here_doc_file)  // Освобождаем here_doc файл
	{
		printf("here_doc_file %s\n", cmd->here_doc_file);
        free(cmd->here_doc_file);
	}
    if (cmd->output_file)  // Освобождаем файл для вывода
	{
		printf("cmd->output_file %s\n", cmd->output_file);
        free(cmd->output_file);
	}
    if (cmd->append_file)  // Освобождаем файл для append
	{
		printf("cmd->append_file %s\n", cmd->append_file);
        free(cmd->append_file);
	}
}

void free_data(t_data *data)
{
    if (data)
    {
        if (data->cmd)
        {
            for (int i = 0; data->cmd[i]; i++)  // Освобождаем команды
            {
                free_cmd(data->cmd[i]);  // Освобождаем каждый элемент структуры команды
                free(data->cmd[i]);      // Освобождаем саму структуру команды
            }
            free(data->cmd);  // Освобождаем массив команд
        }
        free(data);  // Освобождаем основную структуру data
    }
}

int main(int argc, char **argv, char **envp)
{
    (void) argc;
    (void) argv;
    t_data *data;

	data = malloc (sizeof(t_data));
	ft_memset(data, 0, sizeof(t_data));
	data->cmd = malloc(sizeof(t_cmd *) * 2);
	data->cmd[0] = malloc(sizeof(t_cmd));
//	data->cmd[1] = malloc(sizeof(t_cmd));
//	data->cmd[2] = malloc(sizeof(t_cmd));
	data->cmd[1] = NULL;
	ft_memset(data->cmd[0], 0, sizeof(t_cmd));
	data->cmd[0]->cmd = ft_strdup("cat");
//   data->cmd[0]->cmd_arg = ft_strdup("2");
	data->cmd[0]->cmd_arg = NULL; 
//	data->cmd[0]->input_file = ft_strdup("infile.txt");
//	data->cmd[0]->input_file = ft_strdup("input.txt");  ///---------------
	data->cmd[0]->input_file = NULL;
    data->cmd[0]->pos_input = 0;

    data->cmd[0]->here_doc_file = ft_strdup("END");
//	data->cmd[0]->here_doc_file = NULL;
    data->cmd[0]->pos_here_doc = 1;

//	data->cmd[0]->output_file = ft_strdup("outfile.txt");
//	data->cmd[0]->output_file = ft_strdup("output.txt");
    data->cmd[0]->output_file = NULL;
	data->cmd[0]->pos_output = 0;
//	data->cmd[0]->append_file = ft_strdup("outfile.txt");
    data->cmd[0]->append_file = NULL;
    data->cmd[0]->pos_append = 0;


/*	ft_memset(data->cmd[1], 0, sizeof(t_cmd));
	data->cmd[1]->cmd = ft_strdup("cat");
//	data->cmd[1]->cmd_arg = ft_strdup("infile.txt");
    data->cmd[1]->cmd_arg = NULL;
//	data->cmd[1]->input_file = ft_strdup("infile_2.txt");
	data->cmd[1]->input_file = NULL;
    data->cmd[1]->pos_input = 0;

    data->cmd[1]->here_doc_file = NULL;//ft_strdup("END");
    data->cmd[1]->pos_here_doc = 0;

//    data->cmd[1]->output_file = ft_strdup("outfile.txt");
	data->cmd[1]->output_file = NULL;
	data->cmd[1]->pos_output = 0;

	data->cmd[1]->append_file = ft_strdup("outfile.txt");
//    data->cmd[1]->append_file = NULL;//ft_strdup("outfile.txt");
    data->cmd[1]->pos_append = 1;

	ft_memset(data->cmd[2], 0, sizeof(t_cmd));
	data->cmd[2]->cmd = ft_strdup("wc");
	data->cmd[2]->cmd_arg = ft_strdup("-l");
//    data->cmd[2]->cmd_arg = NULL;  
///	data->cmd[2]->input_file = ft_strdup("infile_2.txt");
	data->cmd[2]->input_file = NULL;
    data->cmd[2]->pos_input = 0;
    data->cmd[2]->here_doc_file = NULL;//ft_strdup("END");
    data->cmd[2]->pos_here_doc = 0;
//    data->cmd[2]->output_file = ft_strdup("outfile.txt");
	data->cmd[2]->output_file = NULL;//ft_strdup("outfile.txt");
//	data->cmd[2]->append_file = ft_strdup("outfile.txt");
    data->cmd[2]->append_file = NULL;//ft_strdup("outfile.txt");
    data->cmd[2]->pos_output = 0;
    data->cmd[2]->pos_append = 0;
*/
    data->envp = envp;
    data->nb_pipe = 0;
	printf("main befor choice_execution\n");
	choice_execution(data);
	printf("exit status %i\n", data->exit_status);
	free_data(data);
	return (0);
}


/*
int main(int argc, char **argv, char **envp)
{
    (void) argc;
    (void) argv;
    t_data *data;

	ft_memset(data, 0, sizeof(t_data));
	data.cmd[0]->cmd = "cat"; 
    data.cmd[0]->cmd_arg = NULL;  
	data.cmd[0]->input_file;
    data.cmd[0]->pos_input;
    data.cmd[0]->here_doc_file;
    data.cmd[0]->pos_here_doc;
    data.cmd[0]->output_file; 
    data.cmd[0]->append_file;
    data.cmd[0]->pos_output;
    data.cmd[0]->pos_append;

    data.envp = envp;
    data.nb_pipe = 0;
	choice_execution(&data);
//	printf("exit status %i\n", data->exit_status);
	return (0);
}
*/



/*
   (void) argc;
    (void) argv;
	char *strs[4];
    t_command commands;

	strs[0] = "<<";
	strs[1] = "LIM";
	strs[2] = "cat";
	strs[3] = NULL;

    commands.envp = envp;
	commands.argv = strs;
	//commands.input_file = NULL;
	commands.input_file c;
	//commands.here_doc_file = NULL;
	commands.here_doc_file = "LIM"; 
	//commands.output_file = NULL;
	commands.output_file = "outfile.txt";
	//commands.append_file = NULL;
	//commands.append_file = "outfile.txt";
	commands.is_pipe = 0;
	commands.prev_pipe = 0;
	choice_execution(&commands);
	*/