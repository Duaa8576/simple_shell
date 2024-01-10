#include "shell.h"


/*
 * This function initializes the paths array with
 * the directories in the PATH environment variable.
 * Parameters:
 * None
 *
 * Returns:
 * None
 */
void init_paths(void)
{
	int num_paths;
	char *paths[MAX_PATHS];
	char *path = getenv("PATH");
	char *dir = strtok(path, ":");

	num_paths = 0;
	while (dir != NULL && num_paths < MAX_PATHS)
	{
		paths[num_paths++] = dir;
		dir = strtok(NULL, ":");
	}
}

/*
 * This function searches for the command in
 * the directories in the paths array.
 *
 * Parameters:
 * command (char *): The command to search for
 *
 * Returns:
 * char *: The full path to the command, or NULL if it is not found
 */
char *find_command(char *command)
{
	int num_paths;
	char *paths[MAX_PATHS];
	char *full_path = malloc(MAX_LENGTH);

	for (int i = 0; i < num_paths; i++)
	{
		sprintf(full_path, "%s/%s", paths[i], command);
		if (access(full_path, X_OK) == 0)
		{
			return (full_path);
		}
	}
	free(full_path);
	return (NULL);
}

/*
 * This function executes the command with the given arguments.
 *
 * Parameters:
 * command (char *): The command to execute
 * args (char **): The arguments to the command
 *
 * Returns:
 * None
 */
void execute_command(char *command, char **args)
{
	int num_paths;
	char *paths[MAX_PATHS];
	char *full_path = find_command(command);

	if (full_path == NULL)
	{
		printf("%s: command not found\n", command);
		return;
	}

	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return;
	}
	if (pid == 0)
	{
		execv(full_path, args);
		perror("execv");
		exit(1);
	}
	wait(NULL);
	free(full_path);
}
