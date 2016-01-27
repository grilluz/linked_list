#include <stdlib.h>
#include <limits.h> //for LONG_MAX
#include "List.h"
#include "DSerror.h"

int init_list(pList list, long length, void *data[])
{
	int err;

	if (list == NULL)
		return NULL_LIST_ERR;

	if (length < 0)
		return NEG_LENGTH_ERR;

	list->length = 0;
	list->head = NULL;
	list->tail = NULL;

	for (int i = 0; i < length; i++) {
		err = append(list, data[i], NULL);
		if (err != DS_OK) {
			remove_all(list);
			return err;
		}
	}

	return DS_OK;
}

int remove_all(pList list)
{
	int err;

	if (list == NULL || list->tail == NULL)
		return NULL_LIST_ERR;

	//remove all nodes frome the last one to the first one
	//list->tail->prev is NULL means that there is the last node yet
	while (list->tail->prev != NULL) { 
		list->tail = list->tail->prev;
		err = remove_node(list->tail->next);
		list->tail->next = NULL;
	}

	err = remove_node(list->tail);

	list->length = 0;
	list->head = NULL;
	list->tail = NULL;

	return err;
}

int set_data(pList list, long index, void *data)
{
	int err;

	if (list == NULL)
		return NULL_LIST_ERR;

	if (index < 0 || index >= list->length)
		return INVALID_INDEX;

	if (data == NULL)
		return NULL_DATA_ERR;

	pNode node;

	err = get_node(list, index, &node);
	if (err != DS_OK)
		return err;

	node->data = data;

	return DS_OK;
}


int append(pList list, void *data, pNode *node_out)
{
	pNode node = NULL;
	
	if (list == NULL)
		return NULL_LIST_ERR;

	if (list->length == LONG_MAX)
		return MAX_LENGTH_ERR;

	if (new_node(data, &node) != DS_OK)
		return MALLOC_ERR;

	if (list->head == NULL) {
		//list is empty so add the first node
		list->head = node;
		node->prev = NULL;
	}
	else {
		list->tail->next = node;
		node->prev = list->tail;
	}

	list->tail = node;
	list->length++;

	if (node_out != NULL)
		*node_out = node;
	
	return DS_OK;
}

int push(pList list, void *data, pNode *node_out)
{
	if (list == NULL)
		return NULL_LIST_ERR;

	if (list->length == LONG_MAX)
		return MAX_LENGTH_ERR;

	if (data == NULL)
		return NULL_DATA_ERR;

	pNode node;
	if (new_node(data, &node) != DS_OK)
		return MALLOC_ERR;

	if (list->head == NULL) { 
		//list is empty
		node->next = NULL;
		list->tail = node;
	}
	else {
		list->head->prev = node;
		node->next = list->head;
	}

	list->head = node;
	list->length++;

	if (node_out != NULL)
		*node_out = node;

	return DS_OK;
}

int insert(pList list, long index, void *data, pNode *node_out)
{
	if (list == NULL)
		return NULL_LIST_ERR;

	if (index < 0 || index >= list->length)
		return INVALID_INDEX;

	if (node_out == NULL)
		return OUT_PARAM_NULL;

	pNode node;
	int err;

	if (index == 0) {
		err = push(list, data, &node);
	}
	else if (index == list->length - 1) {
		err = append(list, data, &node);
	}
	else {
		pNode temp;
		err = get_node(list, index, &temp);

		if (new_node(data, &node) != DS_OK)
			return MALLOC_ERR;

		node->next = temp->next;
		node->prev = temp;
		temp->next->prev = node;
		temp->next = node;
	}

	return err;
}

int remove(pList list, pNode node_rm)
{
	if (list == NULL)
		return NULL_LIST_ERR;

	if (node_rm == NULL)
		return NULL_NODE_ERR;

	pNode node = list->head;

	while (node != node_rm) {
		node = node->next;
	}

	if (list->head == node_rm) {
		//remove first node
		list->head = node_rm->next;
		list->head->prev = NULL;
	}
	else if (list->tail == node_rm) {
		//remove last node
		list->tail = list->tail->prev;
		list->tail->next = NULL;
	}
	else {
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}


	int err = remove_node(node_rm);
	if (err == DS_OK)
		list->length--;

	return err;
}

int pop(pList list) 
{
	if (list == NULL)
		return NULL_LIST_ERR;

	int err;

	if (list->tail == list->head) {
		//remove the first and unique node
		err = remove_node(list->head);
		list->head = NULL;
		list->tail = NULL;
	}
	else {
		list->head = list->head->next;
		err = remove_node(list->head->prev);
		list->head->prev = NULL;
	}

	list->length--;

	return err;
}

int get_node(pList list, long index, pNode *node_out_nec)
{
	if (list == NULL)
		return NULL_LIST_ERR;

	if (index < 0 || index >= list->length)
		return INVALID_INDEX;

	if (node_out_nec == NULL)
		return OUT_PARAM_NULL;

	pNode node;

	if (index <= list->length / 2) {
		node = list->head;
		for (int i = 0; i < index; i++) {
			node = node->next;
		}
	}
	else {
		node = list->tail;
		for (int i = list->length - 1; i > index; i--) {
			node = node->prev;
		}
	}

	*node_out_nec = node;

	return DS_OK;
}

int get_index(pList list, pNode node, long *index_out)
{
	if (list == NULL)
		return NULL_LIST_ERR;

	if (node == NULL)
		return NULL_NODE_ERR;

	if (index_out == NULL)
		return OUT_PARAM_NULL;

	long index = 0;
	pNode temp = list->head;
	
	while (temp != node) {
		temp = temp->next;
		index++;

		if (temp == NULL) {
			*index_out = -1;
			return SEARCH_ERROR;
		}
	}
	
	*index_out = index;

	return DS_OK;
}

int move(pList list, long index, direction dir, pNode *node_out)
{
	if (list == NULL)
		return NULL_LIST_ERR;

	if (node_out == NULL)
		return OUT_PARAM_NULL;

	if (index < 0 || index > list->length)
		return INVALID_INDEX;

	if (dir != FORWARD || dir != BACKWARD)
		return INVALID_INPUT;

	pNode node;
	int err = get_node(list, index, &node);
	if (err != DS_OK)
		return err;

	if (dir == FORWARD) {
		if (node == list->tail) {
			node = list->head;
		}
		else {
			node = node->next;
		}
	}
	else {
		if (node == list->head) {
			node = list->tail;
		}
		else {
			node = node->prev;
		}
	}

	*node_out = node;

	return DS_OK;
}