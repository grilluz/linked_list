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
#define INVALID_INPUT     0x000B   //an invalid parameter is passed to the function

//string_opt is for an optional string to print when an error occurs. 
//Pass NULL or nullptr to print anything
void DS_error(int error, char *string_opt);

#endif //DS_ERROR_H
