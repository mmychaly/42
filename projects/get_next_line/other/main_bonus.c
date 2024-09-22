#include <stdio.h>
#include "../get_next_line_bonus.h"

int main(int argc, char *argv[])
{
	int *fds;
	char *line;
    int i;
    int files_left;

    i = 0;
    if (argc < 2)
    {
        write (2, "More files\n", 11);
        return (1);
    }
    fds = malloc(sizeof(int) * (argc - 1));
    if (!fds)
        return (1);
    while (i < (argc - 1))
    {
        fds[i] = open(argv[i + 1], O_RDONLY);
        if (fds[i] == -1)
        {
            perror("Error opening file");
            while (i < argc - 1)
            {
                close(fds[i]);
                i++;
            }
            free(fds);
            return (1);
       }
        i++;
    }

    i = 0;
    files_left = argc - 1;
    while (files_left > 0)
    {
        files_left = 0;
        i = 0;
        while (i < (argc - 1))
        {
            line = get_next_line(fds[i]);
            if (line != NULL)
            {
                printf("%s\n", line);
                free(line);
                files_left++;
            }
            i++;
        }
    }
    i = 0;
    while (i < argc - 1)
    {
        close(fds[i]);
        i++;
    }
    free(fds);
    printf("after close\n");
	return (0);
}

