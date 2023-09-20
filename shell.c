#include "shell.h"
/**
 * main - a function that executes other programs
 * Return: Exit status
 */
char *ORIGINAL_PATH = NULL;
int main()
{
	ORIGINAL_PATH = getenv("PATH");
	prompt();
	return 0;
}

