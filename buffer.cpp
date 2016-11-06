#include <iostream>
#include <cstdlib>

#include "list_node.h"
#include "buffer.h"

using namespace std;

buffer::buffer(int bufferSize,int listNodeSize){
	this->vertices = (list_node*) malloc(bufferSize*sizeof(list_node));
	this->numberOfVertices = 0;
	this->bufferSize = bufferSize;
	this->listNodeSize = listNodeSize;
	for (int i = 0; i < bufferSize; ++i)
	{
		this->vertices[i] = *new list_node(listNodeSize);
	}
}

buffer::~buffer(){
	for (int i = 0; i < bufferSize; ++i) delete (this->vertices+i); //o kimwnas einai guru
	this->numberOfVertices = 0;
	this->bufferSize = INVALID;
	cout<<"deleting buffer"<<endl;
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
   return OK;
}
int buffer::getBufferSize(){
	return this->bufferSize;
}

OK_SUCCESS buffer::resize(int newsize,int mode){
  if(newsize < this->bufferSize) return FAIL;
  int oldsize = this->bufferSize;
  switch (mode) {
    case 1:
      this->vertices = (list_node*) realloc(this->vertices,2*this->bufferSize*sizeof(list_node));
      this->bufferSize = 2*this->bufferSize;
      for(int i = oldsize - 1; i < this->bufferSize; ++i) {
            this->vertices[i] = *new list_node(this->listNodeSize);
      }
      return OK;
    case 2:
      this->vertices = (list_node*) realloc(this->vertices,(newsize + 10)*sizeof(list_node));
      this->bufferSize = newsize + 10;
      for(int i = oldsize - 1; i < this->bufferSize; ++i) {
            this->vertices[i] = *new list_node(this->listNodeSize);
      }
      return OK;
    default: return FAIL;
  }
}