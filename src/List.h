#ifndef	LIST_H
#define LIST_H

#include "Node.h"

typedef struct
{
	pNode head;
	pNode tail;
	long length;
}List, *pList;


int init_list(pList list, long length); //

int remove_all(pList list); //

int set_data(pList list, long index, void* data); //

int append(pList list, void *data, pNode *node_out); //

int push(pList list, void *data, pNode *node_out); //

int insert(pList list, long index, void *data, pNode *node_out);

int remove(pList list, pNode node_rm); //

int pop(pList list, pNode node_rm);

int get_node(pList list, long index, pNode *node_out); //

int get_index(pList list, pNode node, long *index_out); //


#endif //LIST_H