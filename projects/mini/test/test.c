#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    (void) argc;
    (void) argv;
    t_data data;

	data.cmd[0]->cmd; 
    data.cmd[0]->cmd_arg;  
/*	data.cmd[0]->input_file;
    data.cmd[0]->pos_input;
    data.cmd[0]->here_doc_file;
    data.cmd[0]->pos_here_doc;
    data.cmd[0]->output_file; 
    data.cmd[0]->append_file;
    data.cmd[0]->pos_output;
    data.cmd[0]->pos_append;*/

    data.envp = envp;
    data.nb_pipe = 0;
	choice_execution(&data);
	return (0);
}



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