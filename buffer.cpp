#include <iostream>
#include <cstdlib>  

#include "list_node.h"
#include "buffer.h"

using namespace std;

buffer::buffer(int bufferSize){
	this->vertices = new list_node(bufferSize);
	this->numberOfVertices = 0;
	this->bufferSize = bufferSize;
}

buffer::~buffer(){
	delete[] this->vertices;
	this->numberOfVertices = 0;
	this->bufferSize = INVALID;
}

OK_SUCCESS buffer::setNumberOfVertices(int numberOfVertices){
	this->numberOfVertices = numberOfVertices;
	return OK;
}
int buffer::getNumberOfVertices(){
	return this->numberOfVertices;
}

OK_SUCCESS buffer::setBufferSize(int bufferSize){
	this->bufferSize = bufferSize;
}
int buffer::getBufferSize(){
	return this->bufferSize;
}

