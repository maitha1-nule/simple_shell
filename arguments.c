#include "main.h"

/**
 * Main: Takes no parameter
 * Return:0(success)
 */

int main(void)
{
	char input[MAX_INPUT_SIZE};

	char prompt(void) = "#cisfun ";

	while (1)
{
	write(STDOUT_FILENO, prompt, sizeof(prompt));
	if (fgets(input, sizeof(input), stdin) == NULL)
	{
		printf("\n");
		break;
	}
	input[strcspn(input, "\n")] == '\0';
	char *args[MAX_ARG_SIZE];
	char *token = strtok(input, " ");
	int arg_count = 0;

	while (token != NULL && arg_count < MAX_ARG_SIZE)
	{
	args[arg_count] = token;
	token = strtok(NULL, " ");
	arg_count++;
	}


	args[arg_count] = NULL;

	pid_t pid = fork();

	if (pid == -1)
	{
		perror("Fork error");
		exit(Exit_failure);
	}
	else if (pid == 0)
	{
		execvp(args[0], args);
		perror("Command not found");
		exit(EXIT_FAILURE);
		else
	{
		init status;

		waitpid(pid, &status, 0);

		if (EXITED(status) && EXITSTATUS(status) == EXIT_SUCCESS)
		{
			printf("\n");
		}
		else
		{
			fprint(stderr, "./shell: %s: command not found\n", args[0]);
		}
	}
	}
	return (0);
}

