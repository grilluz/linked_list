#ifndef NODE_H
#define NODE_H


typedef struct node
{
	void* data;
	struct node *next;
	struct node *prev;
}Node, *pNode;


//allocate memory for a new node
//return: NEW_NODE_ERR  error
//		  DS_OK         successful
int new_node(void *data, pNode *node_out);

//deallocate memory of a node
//return: NULL_NODE_ERR error
//		  DS_OK         successful
int remove_node(pNode node);

#endif //NODE_H
