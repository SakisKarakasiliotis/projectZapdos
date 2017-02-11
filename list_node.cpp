#include <iostream>
#include <cstdlib>

#include "list_node.h"

using namespace std;

list_node::list_node(int listNodeSize){
	this->nextListNode = INVALID;
	this->numberOfNeighbors = 0;
	this->listNodeSize = LIST_NODE_SIZE;
    for (int i=0; i<LIST_NODE_SIZE; i++) {
        edgeProperty[i] = 0;
    }
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
       try{
           this->neighbor[this->numberOfNeighbors] = edge;
           //cout<<"Adding edge: "<<edge<<endl;
           if((int) this->neighbor[this->numberOfNeighbors] < 0) {
               throw edge;
           }

       }catch (uint32_t e){
           cout<<"Unable to add neighbor on list node "<<e<<endl;
       }
       return OK;

   }
   return FAIL;
}
OK_SUCCESS list_node::setNeighbor(uint32_t edge, int version)
{
   if(this->numberOfNeighbors != INVALID)
   {
       try{
           this->neighbor[this->numberOfNeighbors] = edge;
           this->edgeProperty[this->numberOfNeighbors] = version;
           //cout<<"Adding edge: "<<edge<<endl;
           if((int) this->neighbor[this->numberOfNeighbors] < 0) {
               throw edge;
           }

       }catch (uint32_t e){
           cout<<"Unable to add neighbor on list node "<<e<<endl;
       }
       return OK;

   }
   return FAIL;
}
uint32_t list_node::getNeighbor(int ID){
	try{
        if((int) this->neighbor[ID] < 0 || (int) this->neighbor[ID] == -1163005939){
            throw 1;
        }
    }catch(int e){
        cout<<"Found in list node get neighbor "<<endl;
        cin>>e;
    }
		return this->neighbor[ID];

}

OK_SUCCESS list_node::setEdgeProperty(uint32_t edgeProperty){
	if(this->numberOfNeighbors != FULL){
		this->edgeProperty[this->numberOfNeighbors] = edgeProperty;
		return OK;
	}
	return FAIL;
}

int* list_node::getEdgeProperty(){
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

int list_node::getVersion(int ID) {
    if(ID<0 || ID >= listNodeSize){
        return FAIL;
    }
    return edgeProperty[ID];
}
