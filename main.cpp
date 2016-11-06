#include <iostream>
#include <cstdlib>

#include "defines.h"
#include "list_node.h"
#include "buffer.h"
#include "Q.h"

using namespace std;


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
