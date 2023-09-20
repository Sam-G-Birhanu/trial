#include "shell.h"

extern char **environ;
extern char *ORIGINAL_PATH;
int executeCommand(char **tokens) {
	int result;
	char *programName;
	char *token;
	char *original_path = strdup(ORIGINAL_PATH);
/**	   printf("%s this is the path \n", original_path); **/
	if (strcmp(tokens[0], "exit") == 0) {
		exit(0);
	}


/**	char originalDirectory[1024];

	if (getcwd(originalDirectory, sizeof(originalDirectory)) == NULL) {
		perror("getcwd");
		return -1;
	}
**/
	result = handleBuiltins(tokens);

	if (result != -1) {
		setenv("PATH", original_path, 1);
		return result;
	}


	programName = tokens[0];
/**	char *path = getenv("PATH"); */
	token = strtok(original_path, ":");
	if (programName[0] == '/')
	{
		if (fileExists(programName)) {
		    executePathSpecifiedCmd(programName, tokens);
		    return -1;
		}
	}
	while (token != NULL)
	{
	/**	printf("%s token \n" , token); **/
	      /** token = strtok(NULL, ":");	*/
		char *programPath = malloc(strlen(token) + strlen("/") + strlen(programName) + 1);
		if (programPath == NULL) {
			perror("malloc");
			exit(EXIT_FAILURE);
		}

		strcpy(programPath, token);
		strcat(programPath, "/");
		strcat(programPath, programName);

/**		printf("%s original directory", originalDirectory); **/
/**		printf("%s program path", programPath); **/

		if (fileExists(programPath)) {
			pid_t child = fork();

			if (child == -1) {
				perror("fork");
				exit(EXIT_FAILURE);
			}

			if (child == 0) {
/**				printf("%s original directory", originalDirectory); **/
		/**		printf("%s program path", programPath); **/

/**				if (chdir(originalDirectory) == -1) {
					perror("chdir");
					exit(EXIT_FAILURE);
				}
**/
				char *args[MAX_ARGUMENTS];
				int i; 
				setenv("PATH", original_path, 1);

			/**	char *args[MAX_ARGUMENTS]; **/
				args[0] = programPath;


				for (i = 1; tokens[i] != NULL; i++) {
					args[i] = tokens[i];
				}

				args[i] = NULL;

				execve(programPath, args, environ);
				free(programPath);
				perror(".hsh");
				exit(EXIT_FAILURE);
			} else {
				int status;
				wait(&status);

				if (WIFEXITED(status)) {
					printf("Child process exited with status %d\n", WEXITSTATUS(status));
				}

				free(programPath);
				return 0;
			}
		}

		free(programPath);
		token = strtok(NULL, ":");
	}

	perror(".hsh");
	return -1;
}

