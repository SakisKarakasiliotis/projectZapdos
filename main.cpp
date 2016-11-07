#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>

#include "defines.h"
#include "list_node.h"
#include "buffer.h"
#include "index.h"


using namespace std;

int main(int argc, char const *argv[])
{
	// uint32_t* test;
	// uint32_t *Nodes;
	// int size;
	// buffer* Buffer = new buffer(100,2);
	// cout<<Buffer->getNumberOfVertices()<<endl;
	// if(Buffer->insertNeighbor(0, 2) == FAIL){
	// 	cout<<"FAILED to insert 1st Neighbor"<<endl;
	// 	return 0;
	// }
	// cout<<Buffer->getNumberOfVertices()<<endl;
	// Buffer->setNumberOfVertices(1);
	// cout<< Buffer->getNextListNode(0) <<endl;
	// Buffer->setNextListNode(0,1);
	// cout<< Buffer->getNextListNode(0) <<endl;
	// if(Buffer->insertNeighbor(0, 1) == FAIL){
	// 	cout<<"FAILED to insert 2nd Neighbor"<<endl;
	// 	return 0;
	// }
	// Buffer->setNumberOfVertices(4);
   // if(Buffer->insertNeighbor(3, 2) == FAIL){
	// 	cout<<"FAILED to insert 3rd Neighbor"<<endl;
	// 	return 0;
	// }
   //
	// cout<<"all gewd"<<endl;
	// size= Buffer->getNeighbors(Nodes, 0);
	// cout<< size << endl;
	// for (int i = 0; i < size; ++i)
	// {
	// 	cout<< Nodes[i] << endl;
	// }
   // Buffer->setNextListNode(1,2);
   // cout<< Buffer->getNextListNode(1)<<endl;
	// cout << "Buffer size before double: " << Buffer->getBufferSize() << endl;
	// Buffer->resize(1, 1);
	// cout << "Buffer size after double: " << Buffer->getBufferSize() << endl;
	// if(Buffer->resize(5, 2) == FAIL) cout << "Lol you cheeky bastard" << endl;
	// cout << "Buffer size after this must be same: " << Buffer->getBufferSize() << endl;

	// Buffer->resize(100, 2);
	// cout << "Buffer size after newsize: " << Buffer->getBufferSize() << endl;
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
   string inpout;
   char *part1,part2[80],part3[80],initial[80];
   buffer* Buffer ;
   n_index* Index ;
   buffer* Buffer_inv ;
   n_index* Index_inv ;
   ifstream inpoutFile;
   string in;
   int entry;
   getline(cin,in);
      char get[in.size()+1];
      strcpy(get,in.c_str());

   inpoutFile.open(get);
   getline(inpoutFile,inpout);
   cout<<inpout<<endl;
   char inpoutLine[80];
   strcpy(inpoutLine,inpout.c_str());
   part1= strtok(inpoutLine," ");
   cout<<part1<<endl;
   if(!strcmp(part1,"A")||!strcmp(part1,"Q")){
      cout<<"inside if a or q statement"<<endl;
     while(!strcmp(part1,"A")||!strcmp(part1,"Q")||!strcmp(part1,"F")){
        cout<<"inside  while loop of a,q,f"<<endl;
       if(strcmp(part1,"F")){
          cout<<"cmp with f"<<endl;
         strcpy(initial,part1);
         cout<<"1"<<endl;
         part1=strtok(NULL," ");
         cout<<part1<<endl;
         strcpy(part2,part1);
         cout<<part2<<endl;

         part1=strtok(NULL," ");
         strcpy(part3,part1);
         cout<<part3<<endl;
         if(!strcmp(initial,"A")){
           cout<< "adding to graph" <<endl;
           // TODO AddFunction(part2,part3);
          entry = Index->getEntry(atoi(part2));
          if(entry == FAIL){
             cout<<"LOL OUT OF BOUNDS BITCH"<<endl;
          }else if(entry == INVALID){
             int temp = Buffer->addListNode(4);
             Index->addEntry(temp,atoi(part2));
             Buffer->insertNeighbor(Index->getEntry(atoi(part2)),atoi(part3));
             int temp_inv = Buffer_inv->addListNode(4);
             Index_inv->addEntry(temp_inv,atoi(part3));
             Buffer_inv->insertNeighbor(Index_inv->getEntry(atoi(part3)),atoi(part2));
          }else if(entry!=INVALID){
             Buffer->insertNeighbor(Index->getEntry(atoi(part2)),atoi(part3));
             Buffer->insertNeighbor(Index->getEntry(atoi(part3)),atoi(part2));
          }


         }
         else if(!strcmp(initial,"Q")){
           cout<<"question"<<endl;
           //TODO bfs
         }
      }
       getline(inpoutFile,inpout);
       cout<<"got new line"<<endl;
       if(!inpoutFile){
         break;
       }
       strcpy(inpoutLine,inpout.c_str());
       part1=strtok(inpoutLine," ");
     }
   }
   else{
     cout<< "creating a new graph"<<endl;
      Buffer = new buffer(20,4);
      Index = new n_index(10);
     while(strcmp(part1,"S")){
       //cout<<part1<<" ";
       strcpy(initial,part1);
       part1=strtok(NULL," ");
       strcpy(part2,part1);
       //cout<<part2<<endl;
       //TODO AddFunction()
       int temp = Buffer->addListNode(4);
       Index->addEntry(temp,atoi(initial));
       Buffer->insertNeighbor(Index->getEntry(atoi(initial)),atoi(part2));
       int temp_inv = Buffer_inv->addListNode(4);
       Index_inv->addEntry(temp_inv,atoi(part2));
       Buffer_inv->insertNeighbor(Index_inv->getEntry(atoi(part2)),atoi(initial));
       getline(inpoutFile,inpout);
       if(!inpoutFile){
         break;
       }

       strcpy(inpoutLine,inpout.c_str());
       part1= strtok(inpoutLine," ");
       //cout<<part1<<endl;
     }
   }
   inpoutFile.close();
   cout << "file closed" <<endl;
   //end from reading
   //  delete Buffer;
	// free(test_list_node);

	// cout<<"edw paizei mpalitsa to index"<<endl;
	// index* new_index = new index(10);
	// if (new_index->addEntry(46 , 2) == OK ) {
	// 	cout << "ALL good: within limits entry"<< endl;
	// 	std::cout << "sizeOfIndex : "<< new_index->getSizeOfIndex() << std::endl;
	// 	if (new_index->getEntry(2)==FAIL) {
	// 		std::cout << "cannot get entry 2" << std::endl;
	// 	}
	// }
	// else{
	// 	std::cout << "error : try 1" << std::endl;
	// }

	// if (new_index->addEntry(10 , 11) == OK ) {
	// 	cout << "ALL good: little above limits entry"<< endl;
	// 	std::cout << "sizeOfIndex : "<< new_index->getSizeOfIndex() << std::endl;
	// 	if (new_index->getEntry(11)==FAIL) {
	// 		std::cout << "cannot get entry 2" << std::endl;
	// 	}
	// }
	// else{
	// 	std::cout << "error : try 2" << std::endl;
	// }

	// if (new_index->addEntry(10 , 100) == OK ) {
	// 	cout << "ALL good: way above limits entry"<< endl;
	// 	std::cout << "sizeOfIndex : "<< new_index->getSizeOfIndex() << std::endl;
	// 	if (new_index->getEntry(30)==FAIL) {
	// 		std::cout << "cannot get entry 2" << std::endl;
	// 	}
	// }
	// else{
	// 	std::cout << "error : try 3" << std::endl;
	// }
 //   std::cout << "entry 1 if shown 2 all good" << new_index->getEntry(2) << std::endl;
	// delete new_index;
	cout<<"made it to the end"<<endl;
	return 0;
}
