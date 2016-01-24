//test list functions

#include <stdlib.h>
#include <stdio.h>
#include "../../src/DSerror.h"
#include "../../src/List.h"

#define NUM_NODE 3

typedef struct
{
	int id;
	long number;
}data_t;

void set_struct_data(void* data, int id, long num);
void print_data_list(pList list);

int main()
{
	List list1;
	pNode node;
	void* l_data[NUM_NODE];
	void* data1, *data2;
	int err;

	for (int i = 0; i < NUM_NODE; i++) {
		l_data[i] = malloc(sizeof(data_t));
		
		if (l_data[i] == NULL)
			return 1;

		set_struct_data(l_data[i], i, rand() % 100);
	}

	err = init_list(&list1, NUM_NODE, l_data);
	if (err != DS_OK)
		DS_error(err, NULL);

	printf("List of %d nodes:\n", NUM_NODE);
	print_data_list(&list1);

	data1 = malloc(sizeof(data_t));
	set_struct_data(data1, 10, rand() % 100);
	err = append(&list1, data1, NULL);
	if (err != DS_OK)
		DS_error(err, NULL);

	printf("\nList after append():\n");
	print_data_list(&list1);
	
	data2 = malloc(sizeof(data_t));
	set_struct_data(data2, 11, rand() % 100);
	err = push(&list1, data2, NULL);
	if (err != DS_OK)
		DS_error(err, NULL);

	printf("\nList after push():\n");
	print_data_list(&list1);

	pop(&list1);
	printf("\nList after pop():\n");
	print_data_list(&list1);

	err = get_node(&list1, 2, &node);
	err = remove(&list1, node);
	if (err != DS_OK)
		DS_error(err, NULL);

	printf("\nNode at position %d was removed:\n", 2);
	print_data_list(&list1);

	err = remove_all(&list1);
	if (err != DS_OK)
		DS_error(err, NULL);

	//free all data structures created
	for (int i = 0; i < NUM_NODE; i++) {
		free(l_data[i]);
	}
	free(data1);
	free(data2);

	printf("Press any button to continue...");
	getchar();

	return 0;
}

void set_struct_data(void* data, int id, long num)
{
	if (data == NULL)
		return;

	((data_t*)data)->id = id;
	((data_t*)data)->number = num;
}

void print_data_list(pList list)
{
	pNode node;

	for (int i = 0; i < list->length; i++) {
		get_node(list, i, &node);
		data_t *data = (data_t*)node->data;
		printf("%d:  %ld\n", data->id, data->number);
	}
}