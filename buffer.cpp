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
	for (int i = 0; i < bufferSize; i++) delete (this->vertices+i); //o kimwnas einai guru
   //free(this->vertices);
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
  if(newsize < this->bufferSize && mode==2) return FAIL;
  int oldsize = this->bufferSize;
  switch (mode) {
    case 1:
      this->vertices = (list_node*) realloc(this->vertices,2*this->bufferSize*sizeof(list_node));
      this->bufferSize = 2*this->bufferSize;
      for(int i = oldsize - 1; i < this->bufferSize; i++) {
            this->vertices[i] = *new list_node(this->listNodeSize);
      }
      return OK;
    case 2:
      this->vertices = (list_node*) realloc(this->vertices,(newsize + 10)*sizeof(list_node));
      this->bufferSize = newsize + 10;
      for(int i = oldsize - 1; i < this->bufferSize; i++) {
            this->vertices[i] = *new list_node(this->listNodeSize);
      }
      return OK;
    default:
 
    	return FAIL;
  }
}

ptr buffer::addListNode(int listNodeSize){
	//we add only when buffer is at 80% full, so we double the buffer size
	if (this->numberOfVertices >= 0.8*(this->bufferSize) ){
		if(this->resize(1, 1) == FAIL) return FAIL;
	}
	
	this->setNumberOfVertices(this->getNumberOfVertices() + 1);
	return this->numberOfVertices-1;
}

OK_SUCCESS buffer::insertNeighbor(int offset, int neighborId){

	if (neighborId < 0 || offset > numberOfVertices ){
	
		return FAIL;
	}

	if (this->vertices[offset].getNumberOfNeighbors() == 0){ //here is a new node

		if(this->vertices[offset].setNeighbor((uint32_t) neighborId) == FAIL){
			cout << "Unable to add neighbor on insertNeighbor case 0 returned FAIL space occupied" << endl;
			return FAIL;
		}
		this->vertices[offset].setNumberOfNeighbors(this->vertices[offset].getNumberOfNeighbors()+1);
		return OK;
	}
	else if(this->vertices[offset].getNumberOfNeighbors() < this->listNodeSize && this->vertices[offset].getNumberOfNeighbors()!=FULL){//new neighbor

		if(this->vertices[offset].setNeighbor((uint32_t) neighborId) == FAIL){
			cout << "Unable to add neighbor on insertNeighbor case BETWEEN returned FAIL space occupied" << endl;
			return FAIL;
		}

		this->vertices[offset].setNumberOfNeighbors(this->vertices[offset].getNumberOfNeighbors()+1);
		return OK;
	}
	else if(this->vertices[offset].getNumberOfNeighbors() == FULL){//check next neighbor if empty

		if(this->vertices[offset].getNextListNode()==INVALID){
			this->vertices[offset].setNextListNode(this->addListNode(this->listNodeSize));
			if(this->insertNeighbor(this->vertices[offset].getNextListNode(),neighborId)==FAIL){
				return FAIL;
			}
		}else{

			if(this->insertNeighbor(this->vertices[offset].getNextListNode(),neighborId)==FAIL){
				return FAIL;
			}
		}
		return OK;
	}
	return OK;

}

int buffer::getNeighbors(uint32_t *&neighbors, uint32_t nodeOffset){
	int arraySize=0;
	if(this->vertices[nodeOffset].getNumberOfNeighbors()==0){
		cout<<"No neighbors"<<endl;
		return FAIL;
	}
	uint32_t* neighbors_temp = (uint32_t*) malloc(this->listNodeSize * sizeof(uint32_t));
   neighbors = neighbors_temp;
	while(nodeOffset != INVALID) {
	    if(this->vertices[nodeOffset].getNumberOfNeighbors()==FULL){
			for (int i = 0; i < this->listNodeSize; i++){
				neighbors[i] = this->vertices[nodeOffset].getNeighbor(i);
				cout<<neighbors[i]<<endl;
				arraySize++;
			}
			if (this->vertices[nodeOffset].getNextListNode()==INVALID){
				return arraySize;
			}else{
				neighbors = (uint32_t*) realloc(neighbors, this->listNodeSize * sizeof(uint32_t) * 2);
				nodeOffset = this->vertices[nodeOffset].getNextListNode();
			}

		}
		else{
			for (int i = 0; i < this->vertices[nodeOffset].getNumberOfNeighbors(); i++){
				neighbors[arraySize+i] = this->vertices[nodeOffset].getNeighbor(i);
				arraySize++;
			}
			return arraySize;
		}
	}
   return FAIL;
}

int buffer::getNextListNode(int offset){
	return this->vertices[offset].getNextListNode();
}
OK_SUCCESS buffer::setNextListNode(int offset,int target){
	this->vertices[offset].setNextListNode(target);
	return OK;
}
