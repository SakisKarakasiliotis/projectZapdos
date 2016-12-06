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
#include "bfs.h"



using namespace std;

int main(int argc, char const *argv[])
{
	 //FILE READING VARIABLES
   string inpout;
   char *part1,part2[80],part3[80],initial[80],get[600];
   ifstream inpoutFile;
   string in;
   char inpoutLine[80]={0};
   //GRAPH VARIABLES
   buffer* Buffer ;
   n_index* Index ;
   buffer* Buffer_inv ;
   n_index* Index_inv ;
   //HELPERS
   int entry, lineNumber=0, OPTION=2,entry_inv, j=0;
   

   //START READING FILES FOR GRAPH CREATION
   cout<<"INSERT ENTRY FILE: ";
   do{  
        //TODO FIX THE FUCKING PATHS dUM dUM
        if(OPTION==1){
        	strcpy(get,"C:\\Users\\Windows 8\\projectZapdosClion\\tinyWorkload_FINAL.txt");
        }
        else{
//        	strcpy(get,"C:\\Users\\Windows 8\\projectZapdosClion\\tinyGraph.txt");
//        	strcpy(get,"C:\\Users\\Windows 8\\projectZapdosClion\\a.txt");
//        	strcpy(get,"C:\\Users\\Windows 8\\projectZapdosClion\\b.txt");
//        	strcpy(get,"C:\\Users\\Windows 8\\Desktop\\tiny\\tinyGraph.txt");
        	strcpy(get,"C:\\Users\\Windows 8\\Desktop\\small\\smallGraph.txt");
        }
     

       inpoutFile.open(get);

       getline(inpoutFile,inpout);
       strcpy(inpoutLine,inpout.c_str());
       part1= strtok(inpoutLine," \n\t");
       cout<<"FIRST LINE "<<lineNumber<<" TOKEN: "<<part1<<endl;
       if(!strcmp(part1,"A")||!strcmp(part1,"Q")){
         cout<<"WORK FILE"<<endl;
         while(!strcmp(part1,"A")||!strcmp(part1,"Q")){
           if(strcmp(part1,"F")){
             strcpy(initial,part1);
             part1=strtok(NULL," \n\t");
             strcpy(part2,part1);

             part1=strtok(NULL," \n\t");
             strcpy(part3,part1);
             if(!strcmp(initial,"A")){
               cout<< "ADDING TO GRAPH" <<endl;
              entry = Index->getEntry(atoi(part2));
              if(entry == FAIL){
                 cout<<"OUT OF BOUNDS"<<endl;
              }else if(entry == INVALID){
                 int temp = Buffer->addListNode();
                 Index->addEntry(temp,atoi(part2));
                 Buffer->insertNeighbor(Index->getEntry(atoi(part2)),atoi(part3));
             
                 
              }else if(entry!=INVALID){
                 Buffer->insertNeighbor(Index->getEntry(atoi(part2)),atoi(part3));
                 
              }
              entry_inv = Index_inv->getEntry(atoi(part3));
              if(entry_inv == FAIL){
                 cout<<"OUT OF BOUNDS"<<endl;
              }else if(entry_inv == INVALID){
                 int temp_inv = Buffer_inv->addListNode();
                 Index_inv->addEntry(temp_inv,atoi(part3));
                 Buffer_inv->insertNeighbor(Index_inv->getEntry(atoi(part3)),atoi(part2));
                 //
                 
              }else if(entry_inv!=INVALID){                 
                 Buffer_inv->insertNeighbor(Index_inv->getEntry(atoi(part3)),atoi(part2));
              }


             }
             else if(!strcmp(initial,"Q")){
               cout<<"Question"<<endl;
               cout<<j<<"-------------"<<BBFS(Index, Buffer, atoi(part2), Index_inv, Buffer_inv, atoi(part3), 50)<<" this is the fucking answer"<<endl;
             	j++;
             }
          }
           getline(inpoutFile,inpout);
          
           strcpy(inpoutLine,inpout.c_str());
           part1=strtok(inpoutLine," \n\t");
         }
       }else{
         cout<< "GRAPH CREATION"<<endl;
         Buffer = new buffer(BUFFER_SIZE,LIST_NODE_SIZE);
         Index = new n_index(INDEX_SIZE);
         Buffer_inv = new buffer(BUFFER_SIZE,LIST_NODE_SIZE);
         Index_inv = new n_index(INDEX_SIZE);
        
         while(strcmp(part1,"S")){
           strcpy(initial,part1);
           part1=strtok(NULL," \n\t");
           strcpy(part2,part1);
          
           if(Index->getEntry(atoi(initial))==INVALID){
           		int temp = Buffer->addListNode();
           		Index->addEntry(temp,atoi(initial));
           }
//             cout<<"Index size: "<<Index->getSizeOfIndex()<<endl;
//             cout<<"Index NOE: "<<Index->getNumberOfEntries()<<endl;
//            cout<<"initial "<<Index->getEntry(atoi(initial))<<" part2 "<<atoi(part2)<<endl;
             //TODO: getEntry bullshit number
           Buffer->insertNeighbor(Index->getEntry(atoi(initial)),atoi(part2));
           if(Index_inv->getEntry(atoi(part2))==INVALID){
                      int temp_inv = Buffer_inv->addListNode();
                      Index_inv->addEntry(temp_inv,atoi(part2));
                }
           Buffer_inv->insertNeighbor(Index_inv->getEntry(atoi(part2)),atoi(initial));
           getline(inpoutFile,inpout);
           if(!inpoutFile){
             break;
           }

           strcpy(inpoutLine,inpout.c_str());
           part1= strtok(inpoutLine," \n\t");
             lineNumber++;
         }
         inpoutFile.close();
           cout<<"Before Main call"<<endl;
           GetConnectedComponents(Index, Buffer, Index_inv, Buffer_inv);
           cout<<"After Main call"<<endl;
//           Index_inv->printCCnum();
//           Index->printCCnum();
//          uint32_t* neighbors;
//           int k;
//          neighbors = Buffer->getNeighbors(k, Index->getEntry(1));
//           for (int i = 0; i < (k); i++) {
//               cout<<"neighbors of 0 "<<neighbors[i]<<endl;
//           }
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
