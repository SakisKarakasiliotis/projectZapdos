#include <iostream>
#include <cstdlib>

#include "defines.h"
#include "list_node.h"
#include "buffer.h"
#include "Q.h"

#define QSIZE 100

using namespace std


int main(int argc, char const *argv[])
{
	uint32_t* test;
	buffer* Buffer = new buffer(20);
	cout<<Buffer->getNumberOfVertices()<<endl;
	list_node* test_list_node = new list_node(20);
	test_list_node = (list_node*) realloc(test_list_node, 40*sizeof(list_node));
	for (int i = 0; i < 40; ++i)
	{
		test_list_node->setNeighbor(i);
		test_list_node->setNumberOfNeighbors(i+1);
	}



	test=test_list_node->getNeighbor();
	cout<<test[test_list_node->getNumberOfNeighbors()-1]<<" HEllo "<<endl;
	// delete Buffer;
	free(test_list_node);
	cout<<"hello"<<endl;
	return 0;
}

//
int BFS(nodeIndex* outIndex, buffer* outgoing, uint32_t start, nodeIndex* inIndex, buffer* incoming, uint32_t dest, uint32_t fringeSize)
{
   queue* outFringe = malloc(fringeSize);
   queue* inFringe = malloc(fringeSize);
   bool found = false;

   outFringe->enqueue(start);
   inFringe->enqueue(dest);

   int outNeighbors;
   int inNeighbors;
   int numberOfNeighbors;
   list_node* node;
   OK_SUCCESS* error;
   queue* fringe;
   uint32_t ohterFringe;
   while (!found and !(outFringe.isEmpty() and inFringe.isEmpty()))
   {
      *error = OK;
      if (outFringe->isEmpty())
      {
         node = incoming->getListNode(inIndex->getListHead(inFringe->dequeue(error)));
         numberOfNeighbors = node->getNumberOfNeighbors();
         fringe = inFringe;
      }
      else if (inFringe->isEmpty())
      {
         node = outgoing->getListNode(outIndex->getListHead(outFringe->dequeue(error)));
         numberOfNeighbors = node->getNumberOfNeighbors();
         fringe = outFringe;
      }
      else
      {
         outNeighbors = outgoing->getListNode(outIndex->getListHead(outFringe->checkFrontValue(error)))->getNumberOfNeighbors();
         inNeighbors = incoming->getListNode(inIndex->getListHead(inFringe->checkFrontValue(error)))->getNumberOfNeighbors();
         if (inNeighbors > outNeighbors)
         {
            node = outgoing->getListNode(outIndex->getListHead(outFringe->dequeue(error)));
            numberOfNeighbors = outNeighbors;
            fringe = inFringe;
         }
         else
         {
            node = outgoing->getListNode(outIndex->getListHead(outFringe->dequeue(error)));
            numberOfNeighbors = inNeighbors;
            fringe = outFringe;
         }
      }
      //TODO: expand node, fill fringe, check if found, increment path length
   }
}
