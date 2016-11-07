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
