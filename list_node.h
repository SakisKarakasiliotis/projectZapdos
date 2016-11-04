#ifndef LIST_NODE_H
#define LIST_NODE_H

#include "includes.h"

#define INVALID -1
#define FAIL 0
#define OK 1

typedef int ptr;
typedef uint32_t OK_SUCCESS;

class list_node
{
private:
	uint32_t *neighbor;
	uint32_t *edgeProperty;
	ptr nextListNode;
	int numberOfNeighbors;
	int listNodeSize;
public:
	list_node(int);
	~list_node();

	OK_SUCCESS setNeighbor(uint32_t);
	uint32_t* getNeighbor();

	OK_SUCCESS setEdgeProperty(uint32_t);
	uint32_t* getEdgeProperty();

	OK_SUCCESS setNextListNode(int);
	int getNextListNode();	

	OK_SUCCESS setNumberOfNeighbors(int);
	int getNumberOfNeighbors();	

	OK_SUCCESS setListNodeSize(int);
	int getListNodeSize();	
};

#endif