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
	 //FILE READING VARIABLES
   string inpout;
   char *part1,part2[80],part3[80],initial[80];
   ifstream inpoutFile;
   string in;
   //GRAPH VARIABLES
   buffer* Buffer ;
   n_index* Index ;
   buffer* Buffer_inv ;
   n_index* Index_inv ;
   //HELPERS
   int entry, lineNumber=0, OPTION=2;
   

   //START READING FILES FOR GRAPH CREATION
   cout<<"INSERT ENTRY FILE: ";
   do{  
       if(OPTION!=2){
        cout<<"INSERT WORK FILE: ";
       }
       getline(cin,in);
       char get[in.size()+1];
       strcpy(get,in.c_str());

       inpoutFile.open(get);
       getline(inpoutFile,inpout);
       cout<<"lINE: "<<lineNumber<<" "<<inpout<<endl;
       char inpoutLine[80];
       strcpy(inpoutLine,inpout.c_str());
       part1= strtok(inpoutLine," ");
       cout<<"FIRST LINE "<<lineNumber<<" TOKEN: "<<part1<<endl;
       if(!strcmp(part1,"A")||!strcmp(part1,"Q")){
         cout<<"WORK FILE"<<endl;
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
               cout<< "ADDING TO GRAPH" <<endl;
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
           // if(!inpoutFile){
           //   break;
           // }
           strcpy(inpoutLine,inpout.c_str());
           part1=strtok(inpoutLine," ");
         }
       }else{
         cout<< "GRAPH CREATION"<<endl;
         Buffer = new buffer(20,4);
         Index = new n_index(10);
         cout<<Buffer->getNumberOfVertices()<<" On creation"<<endl;
         Buffer->setNumberOfVertices(10);
         cout<<Buffer->getNumberOfVertices()<< " Fuck you"<<endl;
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
       cout<<"CHOOSE"<<endl<< "0 - QUIT"<<endl<<"OR"<<endl<< "1 - INSERT WORK FILE"<<endl;
       cin>>OPTION;
       if (OPTION == 0)
       {
         inpoutFile.close();
         cout << "EXITING" <<endl;
       }
  }while( OPTION == 1 ); //KEEP READING UNTIL 0
   //end from reading
  
	cout<<"GG WP"<<endl;
	return 0;
}
