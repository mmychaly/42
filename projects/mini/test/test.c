#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    (void) argc;
    (void) argv;
	char *strs[4];
    t_command commands;

	/*strs[0] = "cat";
	strs[1] = NULL;*/

	strs[0] = "<<";
	strs[1] = "LIM";
	strs[2] = "cat";
	strs[3] = NULL;

    commands.envp = envp;
	commands.argv = strs;
	//commands.input_file = NULL;
	commands.input_file = "infile.txt";
	//commands.here_doc_file = NULL;
	commands.here_doc_file = "LIM"; 
	//commands.output_file = NULL;
	commands.output_file = "outfile.txt";
	//commands.append_file = NULL;
	//commands.append_file = "outfile.txt";
	commands.is_pipe = 0;
	commands.prev_pipe = 0;
	choice_execution(&commands);
	return (0);
}