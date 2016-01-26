#include "DSerror.h"
#include <stdio.h>

void DS_error(int error, char *string_opt)
{
	switch (error)
	{
	case DS_OK:
		break;

	case MALLOC_ERR:
		fputs("Impossible allocating memory...", stderr);
		break;

	case NULL_NODE_ERR:
		fputs("Passed a null pointer to node to the function...", stderr);
		break;

	case NULL_LIST_ERR:
		fputs("Passed a null pointer to list to the function...", stderr);

	case MAX_LENGTH_ERR:
		fputs("Reached max length of a list...", stderr);
		break;

	case NEG_LENGTH_ERR:
		fputs("Attempt to assign negative length to list...", stderr);
		break;

	case INVALID_INDEX:
		fputs("Index out of range...", stderr);
		break;

	case SEARCH_ERROR:
		fputs("The list hasn't this node...", stderr);
		break;

	case OUT_PARAM_NULL:
		fputs("Output parameter of the function can't be null...", stderr);
		break;

	case NULL_DATA_ERR:
		fputs("Passed a null pointer to data to the function", stderr);
		break;

	case INVALID_INPUT:
		fputs("Invalid input was passed to the function...", stderr);

	default:
		fputs("Has occurred an error...", stderr);
	}

	if (string_opt != NULL)
		fputs(string_opt, stderr);
}

