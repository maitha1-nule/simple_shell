#include "main.h"


/**
 * main - This is the main entry of our program.
 * @argc: This is an arg count including name of the program
 * @argv: This ia a NULL terminated array of string
 *
 * Return: 0 always at the end.
 */
int main(int argc, char *argv[])
{
	char *buf = NULL;
	size_t count = 0;
	ssize_t read;
	pid_t child;
	int status;
	char **array;
	int i;
	char *token;
	(void)argc;
	(void)argv;

	while (1)
	{
		write(STDOUT_FILENO, "cisfun$ ", 9);
		read = getline(&buf, &count, stdin);
		if (read == -1)
		{
			perror("Exiting the shell..");
			exit(1);
		}
		token = strtok(buf, " \n");
		array = malloc(sizeof(char *) * 1024);
		i = 0;
		while (token)
		{
			array[i] = token;
			token = strtok(NULL, " \n");
			i++;
		}
		array[i] = NULL;
		child = fork();
		if (child == -1)
		{
			perror("failed to spawn a child.");
			exit(41);
		}
		if (child == 0)
		{
			if (execve(array[0], array, NULL) == -1)
		{
		perror("Couldn't execute");
		exit(97);
		}
		}
		else
		{
			wait(&status);
		}
	}
	free(buf);
	return (0);
}
