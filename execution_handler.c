#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"

/**
 * execution_handler -> Executes input command
 * @cmd: The command passed by user
 * @env: Environment variables
 * @arg1: Contains executable for error handling
 * Return: 1 on success, 0 on failure.
 */

int execution_handler(char *cmd, char **env, char arg1)
{
	char *bin_path = find_path(env);
	char *path_with_cmd, *path_tokeniser, *path_to_free;
	char **arr_of_args = NULL;
	int path_attempts = 0;

	arr_of_args = cmd_parser(cmd);
	path_tokeniser = strtok(bin_path, ":");
	path_to_free = path_tokeniser;
	path_attempts = 0;
	path_with_cmd = malloc(sizeof(cmd));
	_strcpy(path_with_cmd, cmd);

	for (; path_tokeniser != NULL; path_attempts++)
	{
		if (access(path_with_cmd, F_OK) == 0)
		{
			execve(path_with_cmd, arr_of_args, NULL);
			free(path_with_cmd);
			free(path_to_free);
			free_2d_array(arr_of_args);
			return (1);
		}

		path_with_cmd = str_concat(path_tokeniser, str_concat
				("/", arr_of_args[0]));

		if (path_attempts != 0)
			path_tokeniser = strtok(NULL, ":");
	}

	write(1, arg1, sizeof_string(arg1) * sizeof(char));
	write(1, "1: ", sizeof("1: "));
	write(1, arr_of_args[0], sizeof(arr_of_args));
	write(1, ": Not Found\n", sizeof(": not found\n"));
	free(path_to_free);
	free(path_with_cmd);
	free_2d_array(arr_of_args);
	return (0);
}
