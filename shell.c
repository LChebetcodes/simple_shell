#include <stdio.h>
#include "main.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

extern char **environ;

/**
 * handle_eof - Handles the end-of-file condition.
 * If the end of file is encounteref, this function exits the program.
 *
 */
void handle_eof(void)
{
	if (feof(stdin))
	{
	printf("\n");
	exit(0);
	}
}

/**
 * execute_command - Executes the user-provided command using execve.
 *
 * @command: The command to execute.
 * This function forks a child process to execute the command. If execve fails,
 * an error message is displayed.
 */
void execute_command(char *command)
{
	pid_t pid;
	char *args[2];

	command[strcspn(command, "\n")] = 0;

	args[0] = command;
	args[1] = NULL;

	pid = fork();
	if (pid == 0)
	{
		if (execve(command, args, environ) == -1)
		{
		perror("./shell");
		exit(1);
		}
	}
	else if (pid < 0)
	{
	perror("Fork failed");
	exit(1);
	}
	else
	{
	wait(NULL);
	}
}

/**
 * main - Main function to drive the shell program.
 *
 * This function displays the prompt, reads the user imput,
 * and calls the necessary
 * functions to execute the commands. It runs in an infinite loop
 * until Ctrl+D (EOF) is pressed.
 * Return: 0 on success
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;

	while (1)
	{
	printf("#cisfun$ ");

	ssize_t read_len = getline(&line, &len, stdin);

	handle_eof();

	if (read_len == -1)
	{
		perror("Error reading input");
		free(line);
		exit(1);
	}

	if (line[0] != '\0')
		{
		execute_command(line);
		}
	}

	free(line);
	return (0);
}
