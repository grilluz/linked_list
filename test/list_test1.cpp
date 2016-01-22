#include <stdio.h>
#include "../src/List.h"
#include "../src/DSerror.h"

int main()
{
	const int number_of_node = 5;
	int err;

	int data[number_of_node];
	List list1;

	err = init_list(&list1, number_of_node);
	if (err != DS_OK) {
		DS_error(err);
		return 1;
	}

	err = remove_all(&list1);
	if (err != DS_OK) {
		DS_error(err);
		return 1;
	}

	return 0; //test passed
}