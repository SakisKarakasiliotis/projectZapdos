#ifndef BUFFER_H
#define BUFFER_H
#include "list_node.h"

class buffer
{
private:
	list_node* vertices;
	int numberOfVertices;
	int bufferSize;

public:
	buffer(int);
	~buffer();

	OK_SUCCESS setNumberOfVertices(int);
	int getNumberOfVertices();

	OK_SUCCESS setBufferSize(int);
	int getBufferSize();

	// int assignListNode(uint32_t)
};

#endif
