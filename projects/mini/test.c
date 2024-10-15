#include "include/minishell.h"

int main(void)
{
	int fd;
	char *line = NULL;
	int i;

    i = 0;
    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return (1);
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s\n", line);
        free(line);
                i++;
        if (i == 3)
        {
            printf("quit leak line\n");
            break ;
        }
    }
    close(fd);
    printf("after close\n");
    printf("File descriptor closed\n\tNext Call = (%s)\n", get_next_line(fd));
	return (0);
}