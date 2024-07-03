// Assignment name : get_next_line
// Expected files : get_next_line.c
// Allowed functions: read, free, malloc
// --------------------------------------------------------------------------------

// Write a function named get_next_line which prototype should be:

// char *get_next_line(int fd);


// Your function must return a line that has been read from the file descriptor passed as parameter. What we call a "line that has been read" is a succesion of 0 to n characters that end with '\n' (ascii code 0x0a) or with End Of File (EOF).

// The line should be returned including the '\n' in case there is one at the end of the line that has been read. When you've reached the EOF, you must store the current buffer in a char * and return it. If the buffer is empty you must return NULL.

// In case of error return NULL. In case of not returning NULL, the pointer should be free-able. Your program will be compiled with the flag -D BUFFER_SIZE=xx, which has to be used as the buffer size for the read calls in your functions.

// Your function must be memory leak free. When you've reached the EOF, your function should keep 0 memory allocated with malloc, except the line that has been returned.

// Calling your function get_next_line in a loop will therefore allow you to read the text available on a file descriptor one line at a time until the end of the text, no matter the size od either the text or one of its lines.

// Make sure that your function behaves well when it reads from a file, from the standard output, from a redirection, etc...

// No call to another function will be done on the file descriptor between 2 calls of get_next_line. Finally we consider that get_next_line has an undefined behaviour when reading from a binary file.


#include <unistd.h> // For read
#include <stdlib.h> // For malloc && free

/*#define BUFFER_SIZE 8192*/

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

char *get_next_line(int fd);

#endif

char	*get_next_line(int fd)
{
	int		i;
	int		bytes;
	char	*buffer;
	char	character;

	if ((fd < 0) || (BUFFER_SIZE <= 0) || (BUFFER_SIZE > INT_MAX))
		return (NULL);
	i = 0;
	bytes = read(fd, &character, 1);
	buffer = malloc(sizeof(char) * (size_t)(BUFFER_SIZE + 1));
	while (bytes > 0)
	{
		buffer[i++] = character;
		if (character == '\n')
			break ;
		bytes = read(fd, &character, 1);
	}
	if ((bytes <= 0) && (i == 0))
		return (free(buffer), NULL);
	buffer[i] = '\0';
	return (buffer);
}


int main()
{
    int fd;
   fd = open("munia.txt",O_RDONLY);
    char *line;

   while((line = get_next_line(fd)))
   {
    	printf("%s",line);
   		free(line);
    }
}
