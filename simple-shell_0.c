#include <stdio.h>
#include "main.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

/**
 * execute_command - Executes a command using execve
 * @line: The command entered by the user
 */
void execute_command(char *line)
{
	pid_t pid;
	int status;
	char *args[] = {line, NULL};

	pid = fork();
	if (pid == -1)
	{
		perror("Error: Fork failed");
		return;
	}

	if (pid == 0) /* Child process */
	{
	if (execve(line, args, environ) == -1)
		{
		fprintf(stderr, "%s: 1: %s: not found\n", line, line);
		exit(EXIT_FAILURE);
		}
	}
	else /* Parent process */
	wait(&status);
}

/**
 * main - Simple UNIX command line interpreter
 * Return: 0 on success
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	while (1)
	{
	if (isatty(STDIN_FILENO))
		printf("($) ");

	nread = getline(&line, &len, stdin);
	if (nread == -1) /* Handle EOF (Ctrl+D) */
	break;

	/* Remove newline character */
	line[strcspn(line, "\n")] = '\0';

	if (strlen(line) != 0) /* Ignore empty input */
	execute_command(line);
	}

	free(line); /* Free allocated memory */
	return (0);
}
