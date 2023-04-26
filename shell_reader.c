#include "shell.h"

/**
  * _fgetc - Read a single character from input stream
  * represented by a file descriptor fd
  * @fd: integer file descriptor
  *
  * Return: char the single character read
  */
char _fgetc(int fd)
{
	char buf[] = {'\0', '\0'};

	read(fd, buf, 1);
	if (buf[0])
		return (buf[0]);
	return (EOF);
}
