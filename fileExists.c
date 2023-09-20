#include "shell.h"
/*
 * fileExists - a function that checks whether an executable exists
 * @filename: a parmeter
 * Return: type int
 */

int fileExists(const char *filename) {
	struct stat buffer;
/**	printf("I am in fileExists.c");
	printf("%s" , filename); **/
	int i = stat(filename, &buffer);
	printf("%d stat", i);
	return (stat(filename, &buffer) == 0);
}

