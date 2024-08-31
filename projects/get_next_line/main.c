#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
	int fd;
	char *line = NULL;;

	fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return (1);
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("in wh %s\n", line);
        free(line);
    }
    close(fd);
    printf("after close\n");
    printf("File descriptor closed\n\tNext Call = (%s)\n", get_next_line(fd));
	return (0);
}

/*made-f0Ar8s12% ./a.out 
---DEBUT---
befor ft_read_fd line_buffer == (null)
in ft_read_fd res_read 21
in ft_read_fd buffer 123456789rtgfdmnbvcxz
line_buffer after ft_strdup 123456789rtgfdmnbvcxz
in ft_read_fd res_read 21
in ft_read_fd buffer 1
[ppxpl]
sre89ge7g19
line_buffer after ft_strjoin 123456789rtgfdmnbvcxz1
[ppxpl]
sre89ge7g19
line_buffer final in ft_read_fd123456789rtgfdmnbvcxz1
[ppxpl]
sre89ge7g19

after ft_read_fd line_buffer == 123456789rtgfdmnbvcxz1
[ppxpl]
sre89ge7g19
befor ft_separator_line 
line_printable in ft_separator_line 123456789rtgfdmnbvcxz1

line_buffer in ft_separator_line [ppxpl]
sre89ge7g19

after ft_separator_line line_buffer == [ppxpl]
sre89ge7g19
line_printable == 123456789rtgfdmnbvcxz1



---FIN---
123456789rtgfdmnbvcxz1

---DEBUT---
befor ft_read_fd line_buffer == [ppxpl]
sre89ge7g19
in ft_read_fd res_read 13
in ft_read_fd buffer 1/h1/4=h5/9+*
line_buffer after ft_strjoin [ppxpl]
sre89ge7g191/h1/4=h5/9+*
line_buffer final in ft_read_fd[ppxpl]
sre89ge7g191/h1/4=h5/9+*

after ft_read_fd line_buffer == [ppxpl]
sre89ge7g191/h1/4=h5/9+*
befor ft_separator_line 
line_printable in ft_separator_line [ppxpl]

line_buffer in ft_separator_line sre89ge7g191/h1/4=h5/9+*

after ft_separator_line line_buffer == sre89ge7g191/h1/4=h5/9+*
line_printable == [ppxpl]



---FIN---
[ppxpl]

---DEBUT---
befor ft_read_fd line_buffer == sre89ge7g191/h1/4=h5/9+*
in ft_read_fd res_read 0
line_buffer final in ft_read_fdsre89ge7g191/h1/4=h5/9+*

after ft_read_fd line_buffer == sre89ge7g191/h1/4=h5/9+*
befor ft_separator_line 
line_printable in ft_separator_line sre89ge7g191/h1/4=h5/9+*
temp[0] == 0
line_buffer in ft_separator_line 

after ft_separator_line line_buffer == 
line_printable == sre89ge7g191/h1/4=h5/9+*


---FIN---
sre89ge7g191/h1/4=h5/9+*
---DEBUT---
befor ft_read_fd line_buffer == 
in ft_read_fd res_read 0
line_buffer final in ft_read_fd
res_read <= 0
line_buffer)[0] == 0

after ft_read_fd line_buffer == (null)
---DEBUT---
in errro if 
line_buffer == (null)
read(fd, 0, 0) < 0    == -1
File descriptor closed
        Next Call = ((null))
made-f0Ar8s12% 
made-f0Ar8s12% cc -Wall -Wextra -Werror *.c
made-f0Ar8s12% ./a.out  
---DEBUT---
befor ft_read_fd line_buffer == (null)
in ft_read_fd res_read 21
in ft_read_fd buffer 123456789rtgfdmnbvcxz
line_buffer after ft_strdup 123456789rtgfdmnbvcxz
in ft_read_fd res_read 21
in ft_read_fd buffer 1
[ppxpl]
sre89ge7g19
line_buffer after ft_strjoin 123456789rtgfdmnbvcxz1
[ppxpl]
sre89ge7g19
line_buffer final in ft_read_fd123456789rtgfdmnbvcxz1
[ppxpl]
sre89ge7g19

after ft_read_fd line_buffer == 123456789rtgfdmnbvcxz1
[ppxpl]
sre89ge7g19
befor ft_separator_line 
line_printable in ft_separator_line 123456789rtgfdmnbvcxz1

line_buffer in ft_separator_line [ppxpl]
sre89ge7g19

after ft_separator_line line_buffer == [ppxpl]
sre89ge7g19
line_printable == 123456789rtgfdmnbvcxz1



---FIN---
123456789rtgfdmnbvcxz1

---DEBUT---
befor ft_read_fd line_buffer == [ppxpl]
sre89ge7g19
in ft_read_fd res_read 13
in ft_read_fd buffer 1/h1/4=h5/9+*
line_buffer after ft_strjoin [ppxpl]
sre89ge7g191/h1/4=h5/9+*
line_buffer final in ft_read_fd[ppxpl]
sre89ge7g191/h1/4=h5/9+*

after ft_read_fd line_buffer == [ppxpl]
sre89ge7g191/h1/4=h5/9+*
befor ft_separator_line 
line_printable in ft_separator_line [ppxpl]

line_buffer in ft_separator_line sre89ge7g191/h1/4=h5/9+*

after ft_separator_line line_buffer == sre89ge7g191/h1/4=h5/9+*
line_printable == [ppxpl]



---FIN---
[ppxpl]

---DEBUT---
befor ft_read_fd line_buffer == sre89ge7g191/h1/4=h5/9+*
in ft_read_fd res_read 0
line_buffer final in ft_read_fdsre89ge7g191/h1/4=h5/9+*

after ft_read_fd line_buffer == sre89ge7g191/h1/4=h5/9+*
befor ft_separator_line 
line_printable in ft_separator_line sre89ge7g191/h1/4=h5/9+*
temp[0] == 0
line_buffer in ft_separator_line 

after ft_separator_line line_buffer == 
line_printable == sre89ge7g191/h1/4=h5/9+*


---FIN---
sre89ge7g191/h1/4=h5/9+*
---DEBUT---
befor ft_read_fd line_buffer == 
in ft_read_fd res_read 0
line_buffer final in ft_read_fd
res_read <= 0
line_buffer)[0] == 0

after ft_read_fd line_buffer == (null)
after close---DEBUT---
in errro if 
line_buffer == (null)
read(fd, 0, 0) < 0    == -1
File descriptor closed
        Next Call = ((null))
made-f0Ar8s12% ls
a.out            get_next_line.h        giant_line.txt  test.txt
get_next_line.c  get_next_line_utils.c  main.c
made-f0Ar8s12% cc -Wall -Wextra -Werror *.c
made-f0Ar8s12% ./a.out 
---DEBUT---
befor ft_read_fd line_buffer == (null)
in ft_read_fd res_read 21
in ft_read_fd buffer 123456789rtgfdmnbvcxz
line_buffer after ft_strdup 123456789rtgfdmnbvcxz
in ft_read_fd res_read 21
in ft_read_fd buffer 1
[ppxpl]
sre89ge7g19
line_buffer after ft_strjoin 123456789rtgfdmnbvcxz1
[ppxpl]
sre89ge7g19
line_buffer final in ft_read_fd123456789rtgfdmnbvcxz1
[ppxpl]
sre89ge7g19

after ft_read_fd line_buffer == 123456789rtgfdmnbvcxz1
[ppxpl]
sre89ge7g19
befor ft_separator_line 
line_printable in ft_separator_line 123456789rtgfdmnbvcxz1

line_buffer in ft_separator_line [ppxpl]
sre89ge7g19

after ft_separator_line line_buffer == [ppxpl]
sre89ge7g19
line_printable == 123456789rtgfdmnbvcxz1



---FIN---
123456789rtgfdmnbvcxz1

---DEBUT---
befor ft_read_fd line_buffer == [ppxpl]
sre89ge7g19
in ft_read_fd res_read 13
in ft_read_fd buffer 1/h1/4=h5/9+*
line_buffer after ft_strjoin [ppxpl]
sre89ge7g191/h1/4=h5/9+*
line_buffer final in ft_read_fd[ppxpl]
sre89ge7g191/h1/4=h5/9+*

after ft_read_fd line_buffer == [ppxpl]
sre89ge7g191/h1/4=h5/9+*
befor ft_separator_line 
line_printable in ft_separator_line [ppxpl]

line_buffer in ft_separator_line sre89ge7g191/h1/4=h5/9+*

after ft_separator_line line_buffer == sre89ge7g191/h1/4=h5/9+*
line_printable == [ppxpl]



---FIN---
[ppxpl]

---DEBUT---
befor ft_read_fd line_buffer == sre89ge7g191/h1/4=h5/9+*
in ft_read_fd res_read 0
line_buffer final in ft_read_fdsre89ge7g191/h1/4=h5/9+*

after ft_read_fd line_buffer == sre89ge7g191/h1/4=h5/9+*
befor ft_separator_line 
line_printable in ft_separator_line sre89ge7g191/h1/4=h5/9+*
temp[0] == 0
line_buffer in ft_separator_line 

after ft_separator_line line_buffer == 
line_printable == sre89ge7g191/h1/4=h5/9+*


---FIN---
sre89ge7g191/h1/4=h5/9+*
---DEBUT---
befor ft_read_fd line_buffer == 
in ft_read_fd res_read 0
line_buffer final in ft_read_fd
res_read <= 0
line_buffer)[0] == 0

after ft_read_fd line_buffer == (null)
after close---DEBUT---
in errro if 
line_buffer == (null)
read(fd, 0, 0) < 0    == -1
File descriptor closed
        Next Call = ((null))*/
