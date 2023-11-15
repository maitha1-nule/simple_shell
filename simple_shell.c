#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

	void display_prompt()
{
	printf("$ ");
	fflush(stdout);
}

	int main()
{
	char input[MAX_INPUT_SIZE];

	while (1)
	{
	display_prompt();

	if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL)
	{
	/* Handle Ctrl+D (end of file)*/
	printf("\n");
	break;
	}

	/* Remove newline character from input*/
	size_t input_length = strlen(input);
	if (input_length > 0 && input[input_length - 1] == '\n')
	{
	input[input_length - 1] = '\0';
	}

	/*Fork a new process*/
	pid_t pid = fork();

	if (pid == -1)
	{
	perror("fork");
	exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
	/*Child process*/

	/*Execute the command*/
	if (execlp(input, input, (char *)NULL) == -1)
	{
	 /*Print an error message if execution fails*/
	perror("execlp");
	exit(EXIT_FAILURE);
	}
	} else
	{
	 /*Parent process*/
	int status;
	if (waitpid(pid, &status, 0) == -1)
	{
	perror("waitpid");
	exit(EXIT_FAILURE);
	}
	}
	}

	printf("Exiting shell...\n");

	return 0;
}

