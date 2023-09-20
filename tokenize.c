#include "shell.h"
/**
 * tokenize - a function that returns a tokenozed version of the input command
 * command: a parameter passed in to be tokenized
 * Return: it returns a pointer to an array of tokens
 */

char **tokenize(const char *command)
{
	int i;
	char *token;
	char **tokens = malloc(sizeof(char *) * 128);
	if (tokens == NULL)
	{
		return NULL;
	}
	i = 0;
	token = strtok((char *)command, " ");
	
	while (token != NULL)
	{
		tokens[i++] = strdup(token);
		token = strtok(NULL, " ");
	}
	
	tokens[i] = NULL;
	return tokens;
}
