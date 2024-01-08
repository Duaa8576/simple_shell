#include "shell.h"

/**
 * bfree - to free pointer
 * @ptr: address
 *
 * Return: two option
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
