#ifndef BUFFER_H
#define BUFFER_H

#include "defines.h"
#include "list_node.h"

class buffer
{
private:
	list_node* vertices;
	int numberOfVertices;
	//the next add should go here
	int bufferSize;
	//geniko megethos array vertices
	int listNodeSize;
	//poso tha einai o pinakas neighbors
public:
	buffer(int,int);
	~buffer();

	OK_SUCCESS setNumberOfVertices(int);
	int getNumberOfVertices();

	OK_SUCCESS setBufferSize(int);
	int getBufferSize();

	//modes are 1:double 2:resize to newsize //
	OK_SUCCESS resize(int newsize,int mode);
	ptr addListNode();
	OK_SUCCESS insertNeighbor(int offset, int neighborId);
	uint32_t * getNeighbors(int& NON, int nodeOffset);

   int getNextListNode(int offset);
	OK_SUCCESS setNextListNode(int offset,int target);
};

#endif
