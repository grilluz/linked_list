//test init_list() and remove_all() functions

#include <stdlib.h>
#include <stdio.h>
#include "../../src/List.h"
#include "../../src/DSerror.h"

int main()
{
	const int number_of_node = 5;
	int err = 0;

	void *data[number_of_node];
	List list1;

	//initialize data
	for (int i = 0; i < number_of_node; i++) {
		data[i] = malloc(sizeof(int));
		*(int*)data[i] = i + 5;
		printf("%d  ", *((int*)data[i]));
	}

	//create new list
	err = init_list(&list1, number_of_node, data);
	if (err != DS_OK) {
		DS_error(err, NULL);
		return 1;
	}

	err = remove_all(&list1);
	if (err != DS_OK) {
		DS_error(err, NULL);
		return 1;
	}

	for (int i = 0; i < number_of_node; i++) {
		free(data[i]);
	}

	printf("\nPress any button to continue...");
	getchar();

	return 0; //test passed
}