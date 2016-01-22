#ifndef DS_ERROR_H
#define DS_ERROR_H

#define DS_OK             0x0000   //no error

#define MALLOC_ERR        0x0001   //error of malloc
#define NULL_NODE_ERR     0x0002   //passing a null node pointer

#define NULL_LIST_ERR     0x0003   //passing a null list pointer
#define MAX_LENGTH_ERR    0x0004   //reached max length of a data structure
#define NEG_LENGTH_ERR    0X0005   //attempt to initialize negative length
#define INVALID_INDEX     0x0006   //index out of range
#define SEARCH_ERROR      0x0007   //in the list there isn't the node looked for
#define OUT_PARAM_NULL    0x0008   //can't pass to output parameter function a null value
#define NULL_DATA_ERR     0x000A   //

void DS_error(int error);

#endif //DS_ERROR_H
