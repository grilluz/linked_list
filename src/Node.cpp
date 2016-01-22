#include <stdlib.h>
#include "Node.h"
#include "DSerror.h"


int new_node(void* data, pNode *node_out)
{
	pNode node = (pNode)malloc(sizeof(Node));

	if (node == NULL) 
		return MALLOC_ERR;

	node->data = data;
	node->next = NULL;
	node->next = NULL;

	if (node_out != NULL)
		*node_out = node;

	return DS_OK;
}


int remove_node(pNode node)
{
	if (node == NULL)
		return NULL_NODE_ERR;

	free(node);

	return DS_OK;
}