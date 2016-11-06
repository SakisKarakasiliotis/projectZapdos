#ifndef LIST_NODE_H
#define LIST_NODE_H

#include "defines.h"

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

	//You should raise the numberOfNeighbors
	OK_SUCCESS setNeighbor(uint32_t);

	//THIS PROPABLY IS FUCKED UP
	uint32_t getNeighbor(int ID);

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
