#include "shell.h"
/**
 * handle_built_ins - a function that handles built-in commands
 * @tokens: a parameter
 * Return: type int
 */

int handleBuiltins(char **tokens)
{
	if (tokens[0] == NULL) {
		return 0;
	}

	if (strcmp(tokens[0], "exit") == 0) {
		exit(0);
	} else if (strcmp(tokens[0], "cd") == 0)
	{
		if (tokens[1] != NULL)
		{
			if (chdir(tokens[1]) == -1)
			{
				perror("chdir");
			}
		}
		else
		{
			struct passwd *pw = getpwuid(getuid());
			if (pw != NULL) {
				if (chdir(pw->pw_dir) == -1) {
					perror("chdir");
				}
			}
		}
		return 0;
	}
	else if (strcmp(tokens[0], "pwd") == 0) {
		char cwd[1024];
		if (getcwd(cwd, sizeof(cwd)) != NULL) {
			printf("%s\n", cwd);
		} else {
			perror("getcwd");
		}
		return 0;
	}

	return -1;
}
