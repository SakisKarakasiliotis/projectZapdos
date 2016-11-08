#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include "defines.h"


using namespace std;

int ReadFile(char* source){
  string part1,part2,part3,inpout;
  ifstream inpoutFile;

  inpoutFile.open(source);
  getline(inpoutFile,inpout);
  cout<<inpout<<endl;
  part1=inpout.substr(0,1);
  cout<<part1<<endl;
  if(!part1.compare("A")||!part1.compare("Q")){
    while(!part1.compare("A")||!part1.compare("Q")||!part1.compare("F")){
      if(part1.compare("F")){
        part2=inpout.substr(2,1);
        cout<<part2<<endl;
        part3=inpout.substr(4,1);
        cout<<part3<<endl;
        if(!part1.compare("A")){
          cout<< "adding to graph" <<endl;
          // TODO AddFunction(part2,part3);
        }
        else if(!part1.compare("Q")){
          cout<<"question"<<endl;
          // TODO QueryFunction(part2,part3);//bf
        }
     }
      getline(inpoutFile,inpout);
      if(!inpoutFile){
        break;
      }
      part1=inpout.substr(0,1);
    }
  }
  else{
    cout<< "creating a new graph"<<endl;
    //TODO CreateGraph();
    while(part1.compare("S")){
      part2=inpout.substr(2,1);
      //TODO AddFunction()
      getline(inpoutFile,inpout);
      if(!inpoutFile){
        break;
      }
      part1=inpout.substr(0,1);
    }
  }
  inpoutFile.close();
  cout << "file closed" <<endl;
  return 1;
}

// int main(){
//   string in;
//   getline(cin,in);
//   char get[in.size()+1];
//   strcpy(get,in.c_str());
//   ReadFile(get);
//
//
//   return 0;
// }

// OLD MAIN FILES
// 
// // uint32_t* test;
  // uint32_t *Nodes;
  // int size;
  // buffer* Buffer = new buffer(100,2);
  // cout<<Buffer->getNumberOfVertices()<<endl;
  // if(Buffer->insertNeighbor(0, 2) == FAIL){
  //  cout<<"FAILED to insert 1st Neighbor"<<endl;
  //  return 0;
  // }
  // cout<<Buffer->getNumberOfVertices()<<endl;
  // Buffer->setNumberOfVertices(1);
  // cout<< Buffer->getNextListNode(0) <<endl;
  // Buffer->setNextListNode(0,1);
  // cout<< Buffer->getNextListNode(0) <<endl;
  // if(Buffer->insertNeighbor(0, 1) == FAIL){
  //  cout<<"FAILED to insert 2nd Neighbor"<<endl;
  //  return 0;
  // }
  // Buffer->setNumberOfVertices(4);
   // if(Buffer->insertNeighbor(3, 2) == FAIL){
  //  cout<<"FAILED to insert 3rd Neighbor"<<endl;
  //  return 0;
  // }
   //
  // cout<<"all gewd"<<endl;
  // size= Buffer->getNeighbors(Nodes, 0);
  // cout<< size << endl;
  // for (int i = 0; i < size; ++i)
  // {
  //  cout<< Nodes[i] << endl;
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
  //  test_list_node->setNeighbor(i);
  //  test_list_node->setNumberOfNeighbors(i+1);
  // }

  // test=test_list_node->getNeighbor();
  // cout<<test[test_list_node->getNumberOfNeighbors()-1]<<" HEllo "<<endl;