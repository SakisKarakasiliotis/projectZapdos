#include <iostream>
#include <cstdlib>  

#include "list_node.h"

using namespace std;

list_node::list_node(int listNodeSize){
	this->neighbor = (uint32_t*) malloc(listNodeSize*sizeof(uint32_t));
	this->edgeProperty = (uint32_t*) malloc(listNodeSize*sizeof(int32_t));
	this->nextListNode = INVALID;
	this->numberOfNeighbors = 0;
	this->listNodeSize = listNodeSize;
}

list_node::~list_node(){
	free(this->neighbor);
	free(this->edgeProperty);
	this->nextListNode = INVALID;
	this->numberOfNeighbors = 0;
	this->listNodeSize = INVALID;
	cout<<"List node Destructed"<<endl;
}

OK_SUCCESS list_node::setNeighbor(uint32_t edge)
{
   if(this->numberOfNeighbors != INVALID)
   {
      this->neighbor[this->numberOfNeighbors] = edge;
      //TODO for testing numberOfNeighbors++;
      return OK;
   }
   return FAIL;
}
uint32_t* list_node::getNeighbor(){
	if(this->numberOfNeighbors){
		return this->neighbor;
	}
	return NULL;
}

OK_SUCCESS list_node::setEdgeProperty(uint32_t edgeProperty){
	if(this->numberOfNeighbors != FULL){
		this->edgeProperty[this->numberOfNeighbors] = edgeProperty;
		//TODO for testing numberOfNeighbors++;
		return OK;
	}
	return FAIL;
}

uint32_t* list_node::getEdgeProperty(){
	if(this->numberOfNeighbors){
		return this->edgeProperty;
	}
	return NULL;
}

OK_SUCCESS list_node::setNextListNode(int nextListNode){
	if(this->nextListNode == INVALID){
		this->nextListNode = nextListNode;
		return OK;
	}
	return FAIL;
}

int list_node::getNextListNode(){
	return this->nextListNode;
}

OK_SUCCESS list_node::setNumberOfNeighbors(int numberOfNeighbors){
	if (numberOfNeighbors == this->listNodeSize){
		this->numberOfNeighbors = FULL;
	}else{
		this->numberOfNeighbors = numberOfNeighbors;
	}
	return OK;
}

int list_node::getNumberOfNeighbors(){
	return this->numberOfNeighbors;
}

OK_SUCCESS list_node::setListNodeSize(int listNodeSize){
	this->listNodeSize = listNodeSize;
	return OK;
}

int list_node::getListNodeSize(){
	return this->listNodeSize;
}
