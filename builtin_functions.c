#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "main.h"

/**
 * builtin_handler -> Handles builtin functions execution
 * @cmd: user input command to run
 * @envp: Environment variables
 */

int builtin_handler(char *cmd, char *envp[])
{
	char **parsed_cmd = NULL;
	parsed_cmd = cmd_parser(cmd);

	if (_strcmp(parsed_cmd[0], "env") == 0)
	{
		print_env(envp);
		free_2d_array(parsed_cmd);
		return (1);
	}
	else if (_strcmp(parsed_cmd[0], "exit") == 0)
		{
			free_2d_array(parsed_cmd);
			exit(0);
			return (1);
		}
	else if (_strcmp(parsed_cmd[0], "cd") == 0)
		{
			if (change_dir(parsed_cmd, envp) == 1)
			{
				free_2d_array(parsed_cmd);
				return (1);
			}
			free_2d_array(parsed_cmd);
			return (0);
		}
	free_2d_array(parsed_cmd);
	return (0);
}

/**
 * change_dir -> cd command
 * @parsed_cmd: cmd with parameters
 * @envp: enviroment variables
 */

int change_dir(char **parsed_cmd, char *envp[])
{
	if (parsed_cmd[1] == NULL)
	{
		chdir(find_home_dir(envp));
		return (1);
	}
	else if (_strcmp(parsed_cmd[1], "-") == 0)
		chdir(" ..");
	else if (access(parsed_cmd[1], F_OK) == 0)
		chdir(parsed_cmd[1]);
	else if (parsed_cmd[2] != NULL)
	{
		write(1, "bash: cd: too many arguements\n",
				sizeof("bash: cd: too many arguements\n"));
	}
	else
	{
		write(1, "bash: cd: ", sizeof("bash: cd: ") * sizeof(char));
		write(1, parsed_cmd[1], sizeof_string(parsed_cmd[1]));
		write(1, ": No such file or directory\n",
				sizeof(": No such file or directory\n") * sizeof(char));
	}
	return (1);
}

/**
 * find_home_dir -> Finds home directory for in use cd
 * @envp: The variable to parse through
 * Return: Home directory
 */

char *find_home_dir(char * envp[])
{
	int loop;
	char *home_path;
	char *rm_home;

	loop = 0;

	while (envp[loop] != NULL)
	{
		if (_contains(envp[loop], "HOME=") == 1)
			rm_home = envp[loop];

		loop++;
	}

	home_path = malloc((sizeof(rm_home) -5) * sizeof(char));

	for (loop = 5; rm_home[loop] != '\0'; loop++)
		home_path[loop] - 5 = rm_home[loop];

	free(rm_home);

	return (home_path);
}

/**
 * print_env -> Prints the environment variables
 * @envp: The environment variables
 * Return: 1 on success
 */

int print_env(char * envp[])
{
	for (int loop = 0; envp[loop] != NULL; loop++)
	{
		write(1, envp[loop], sizeof_string(envp[loop]));
		write(1, "\n", 1);
	}
	return (1);
}
