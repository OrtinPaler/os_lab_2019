#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "revert_string.h"

int main(int argc, char *argv[])
{
	if (argc != 2){
        printf("\nUsage: %s string_to_revert\n", argv[0]);

        char *reverted_str = malloc(sizeof(char) * (strlen(argv[0]) + 1));
        strcpy(reverted_str, argv[0]);

        RevertString(reverted_str);

        printf("Reverted: %s\n\n", reverted_str);
        free(reverted_str);

		return -1;
	}

	char *reverted_str = malloc(sizeof(char) * (strlen(argv[1]) + 1));
	strcpy(reverted_str, argv[1]);

	RevertString(reverted_str);

	printf("\nReverted: %s\n\n", reverted_str);
	free(reverted_str);
	return 0;
}

