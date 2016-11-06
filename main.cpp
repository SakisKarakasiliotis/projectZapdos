#include <iostream>
#include <cstdlib>

#include "list_node.h"
#include "buffer.h"
#include "index.h"


using namespace std;

int main(int argc, char const *argv[])
{
	uint32_t* test;
	buffer* Buffer = new buffer(20,5);
	// cout<<Buffer->getNumberOfVertices()<<endl;
	// list_node* test_list_node = new list_node(20);
	// test_list_node = (list_node*) realloc(test_list_node, 40*sizeof(list_node));
	// for (int i = 0; i < 40; ++i)
	// {
	// 	test_list_node->setNeighbor(i);
	// 	test_list_node->setNumberOfNeighbors(i+1);
	// }
	
	// test=test_list_node->getNeighbor();
	// cout<<test[test_list_node->getNumberOfNeighbors()-1]<<" HEllo "<<endl;
	 delete Buffer;
	// free(test_list_node);

	cout<<"edw paizei mpalitsa to index"<<endl;
	index* new_index = new index(10);
	if (new_index->addEntry(46 , 2) == OK ) {
		cout << "ALL good: within limits entry"<< endl;
		std::cout << "sizeOfIndex : "<< new_index->getSizeOfIndex() << std::endl;
		if (new_index->getEntry(2)==FAIL) {
			std::cout << "cannot get entry 2" << std::endl;
		}
	}
	else{
		std::cout << "error : try 1" << std::endl;
	}

	if (new_index->addEntry(10 , 11) == OK ) {
		cout << "ALL good: little above limits entry"<< endl;
		std::cout << "sizeOfIndex : "<< new_index->getSizeOfIndex() << std::endl;
		if (new_index->getEntry(11)==FAIL) {
			std::cout << "cannot get entry 2" << std::endl;
		}
	}
	else{
		std::cout << "error : try 2" << std::endl;
	}

	if (new_index->addEntry(10 , 100) == OK ) {
		cout << "ALL good: way above limits entry"<< endl;
		std::cout << "sizeOfIndex : "<< new_index->getSizeOfIndex() << std::endl;
		if (new_index->getEntry(30)==FAIL) {
			std::cout << "cannot get entry 2" << std::endl;
		}
	}
	else{
		std::cout << "error : try 3" << std::endl;
	}
   std::cout << "entry 1 if shown 2 all good" << new_index->getEntry(2) << std::endl;
	delete new_index;
	return 0;
}

//
// int BFS(NodeIndex* outgoing, NodeIndex* incoming, uint32_t start, uint32_t dest)
// {
//
// }
