#include <stdio.h>
#include "../src/Node.h"
#include "../src/DSerror.h"


int main()
{
	int err;

	const int number_of_node = 3;
	pNode node[number_of_node];
	int data[number_of_node];

	for (int i = 0; i < number_of_node; i++) {
		data[i] = i * 55;

		err = new_node(&data[i], &node[i]);
		if (err != DS_OK) {
			DS_error(err);
			return 1;
		}
	}

	for (int i = 0; i < number_of_node; i++) {
		printf("Node %d: %d\n", i, *((int*)node[i]->data));
	}

	for (int i = 0; i < number_of_node; i++) {
		err = remove_node(node[i]);
		if (err != DS_OK) {
			DS_error(err);
			return 1;
		}
	}

	printf("\nTest passed...\n");

	//try DS_error function
	printf("\nTrying DS_error function...\n");
	node[0] = NULL;
	err = remove_node(node[0]);
	if (err != DS_OK)
		DS_error(err);

	printf("\n\nPremere un tasto per continuare...");
	getchar();

	return 0;  //test passed
}