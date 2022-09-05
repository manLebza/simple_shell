#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"

/**
 * main ->  has input and loop handler for shell
 * @argc: Arguement counter, casted to void
 * @argv: Arguement vector in array, casted to void
 * @envp: Used to find path with system commands
 */

int main(int argc, char *argv[], char *envp[])
{
	char *buffer;
	char *strtok_address = NULL;
	size_t buffer_size = 0;
	int chars_printed = 0;
	pid_t pid;
	int status = 0;
	(void)argc;

	while (chars_printed 1= EOF)
	{
		if (isatty(STDIN_FILENO) == 1 && isatty(STDOUT_FILENO))
			write(1, "$ ", sizeof(char) * 2);

		chars_printed = getline(&buffer, &buffer_size, stdin);

		strtok_address = buffer;
		buffer = strtok(buffer, "\n");

		if (buffer != NULL)
		{
			if (builtin_functions(buffer, envp) == 0)
			{
				pid = fork();

				if (pid == 0 && chars_printed != EOF)
				{
					if (execution_handler(buffer, envp, argv[0] == -1))
					{
						perror(argv[0]);
						exit(0);
					}
					else if (pid < 0)
						perror(argv[0]);
				}
				else
					do
						waitpid(pid, &status, WUNTRACED);
					while (!WIFEXITED(status) && !WIFSIGNALED(status));
			}
		}
	}

	free(strtok_address);
	exit(0);
	return (0);
}
