#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>

#include "defines.h"
#include "list_node.h"
#include "buffer.h"
#include "index.h"
#include "bfs.h"
#include "updateIndex.h"


using namespace std;

int main(int argc, char const *argv[])
{


//FILE READING VARIABLES -----------------------------------------------------------------------------------------------
   string inpout;
   char *part1,part2[80],part3[80],initial[80],get[600];
   ifstream inpoutFile;
   string in;
   char inpoutLine[80]={0};
//GRAPH VARIABLES ------------------------------------------------------------------------------------------------------
   buffer* Buffer ;
   n_index* Index ;
   buffer* Buffer_inv ;
   n_index* Index_inv ;
   updateIndex* update_index = new updateIndex();
//HELPERS --------------------------------------------------------------------------------------------------------------
   int entry=0, lineNumber=0, OPTION=2,entry_inv=0, numberOfQuestions=0, BFSresult;

//START READING FILES FOR GRAPH CREATION--------------------------------------------------------------------------------
   cout<<"INSERT ENTRY FILE: "<<endl;
   do{
        //TODO: SELECT PATH ACCORDING TO FILE REQUIRED !!!!!!!
        if(OPTION==1){
        	strcpy(get,"C:\\Users\\Windows 8\\projectZapdosClion\\tinyWorkload_FINAL.txt");
        }
        else{
//        	strcpy(get,"C:\\Users\\Windows 8\\projectZapdosClion\\a.txt");
//        	strcpy(get,"C:\\Users\\Windows 8\\projectZapdosClion\\b.txt");
//        	strcpy(get,"C:\\Users\\Windows 8\\Desktop\\tiny\\tinyGraph.txt");
        	strcpy(get,"C:\\Users\\Windows 8\\Desktop\\small\\smallGraph.txt");
        }

// Initializing FILE getting first token--------------------------------------------------------------------------------
       inpoutFile.open(get);
       getline(inpoutFile,inpout);
       strcpy(inpoutLine,inpout.c_str());
       part1= strtok(inpoutLine," \n\t");
       cout<<"FIRST LINE "<<lineNumber<<" TOKEN: "<<part1<<endl;

// Token selected check for case Addition/Question or Creation----------------------------------------------------------

       if(!strcmp(part1,"A")||!strcmp(part1,"Q")){
// -------------!! Workload execution started !!!----------------------------------------------------------------------
         cout<<"WORK FILE"<<endl;
         while(!strcmp(part1,"A")||!strcmp(part1,"Q")){
           if(strcmp(part1,"F")){

             strcpy(initial,part1);
             part1=strtok(NULL," \n\t");
             strcpy(part2,part1);
             part1=strtok(NULL," \n\t");
             strcpy(part3,part1);
// Case A adding entry to Graph-----------------------------------------------------------------------------------------
             if(!strcmp(initial,"A")){
                 cout<< "ADDING TO GRAPH" <<endl;
// Updating outgoing Index ---------------------------------------------------------------------------------------------
                 entry = Index->getEntry(atoi(part2));
                  if(entry == FAIL){
                     cout<<"OUT OF BOUNDS on Index entry "<<atoi(part2)<<" and "<<atoi(part3)<<endl;
                      return FAIL;
                  }
                  else if(entry == INVALID){
                     int temp = Buffer->addListNode();
                     Index->addEntry(temp,atoi(part2));
                     Buffer->insertNeighbor(Index->getEntry(atoi(part2)),atoi(part3));
                      int possibleCCnum = Index->getCCnum( atoi(part3) );
                      if(possibleCCnum == FAIL) {
                          cout<<"Requested Node "<<atoi(part3)<<" is out of bounds on getccnum"<<endl;
                          return FAIL;
                      }
                      if( possibleCCnum != INVALID )
                      {
                          Index->setCCnum(atoi(part2), possibleCCnum);
                      }
                      else
                      {
                          possibleCCnum = Index->getTotalConnectedComponents();
                          Index->setTotalConnectedComponents(Index->getTotalConnectedComponents()+1);
                          Index->setCCnum(atoi(part3), possibleCCnum);
                          Index->setCCnum(atoi(part2), possibleCCnum);
                      }
                  }
                  else if(entry!=INVALID){
                     Buffer->insertNeighbor(Index->getEntry(atoi(part2)),atoi(part3));
                      int possibleCCnum = Index->getCCnum(atoi(part2));
                      if(possibleCCnum == FAIL){
                          cout<<"Requested Node "<<atoi(part2)<<" is out of bounds on getccnum"<<endl;
                          return FAIL;
                      }
                      if(possibleCCnum == INVALID){
                          possibleCCnum = Index->getCCnum( atoi(part3) );
                          if( possibleCCnum != INVALID){
                              Index->setCCnum(atoi(part2), possibleCCnum);
                          }
                          else{
                              possibleCCnum = Index->getTotalConnectedComponents();
                              Index->setTotalConnectedComponents(Index->getTotalConnectedComponents()+1);
                              Index->setCCnum(atoi(part3), possibleCCnum);
                              Index->setCCnum(atoi(part2), possibleCCnum);
                          }
                      }
                      else{
                          int goalNodeCCnum = Index->getCCnum(atoi(part3));
                          if(goalNodeCCnum == INVALID){
                              Index->setCCnum(atoi(part3),possibleCCnum);
                          }
                          else{
                              if(possibleCCnum != goalNodeCCnum){
                                  int foundInUpdateIndex = update_index->findConnection(possibleCCnum,goalNodeCCnum);
                                  if(foundInUpdateIndex == NOT_IN_UPDATE_INDEX){
                                      update_index->addNewConnection(possibleCCnum,goalNodeCCnum);
                                  }
                                  else if(foundInUpdateIndex == FAIL){
                                      cout<<"out of bounds in adding to update index "<<possibleCCnum << " and "<< goalNodeCCnum <<endl;
                                      return FAIL;
                                  }
                                  else{
                                      cout<<"found in update index from "<<possibleCCnum << " to " << goalNodeCCnum << endl;
                                  }
                              }
                          }
                      }
                  }

// Updating incoming Index ---------------------------------------------------------------------------------------------
                  entry_inv = Index_inv->getEntry(atoi(part3));
                  if(entry_inv == FAIL){
                      cout<<"OUT OF BOUNDS on Inverted Index entry "<<atoi(part2)<<" and "<<atoi(part3)<<endl;
                      return FAIL;
                  }
                  else if(entry_inv == INVALID){
                     int temp_inv = Buffer_inv->addListNode();
                     Index_inv->addEntry(temp_inv,atoi(part3));
                     Buffer_inv->insertNeighbor(Index_inv->getEntry(atoi(part3)),atoi(part2));
                  }
                  else if(entry_inv!=INVALID){
                     Buffer_inv->insertNeighbor(Index_inv->getEntry(atoi(part3)),atoi(part2));
                  }
// End of case A -------------------------------------------------------------------------------------------------------
             }

// Case Q for question on the graph ------------------------------------------------------------------------------------
             else if(!strcmp(initial,"Q")){
               cout<<"Question "<<numberOfQuestions<<":"<<endl;
                   int startNode = atoi(part2);
                   int goalNode = atoi(part3);
               if( Index->getCCnum(startNode) != Index->getCCnum(goalNode) ){
                   int hasUpdateConnection = update_index->findConnection( Index->getCCnum(startNode), Index->getCCnum(goalNode) );
                   if( hasUpdateConnection == NOT_IN_UPDATE_INDEX )
                   {
                       cout<<"No path between "<<startNode<<" and "<<goalNode<<endl;
                   }
                   else if(hasUpdateConnection == ALREADY_IN_UPDATE_INDEX)
                   {
                       BFSresult = BBFS(Index, Buffer, startNode, Index_inv, Buffer_inv, goalNode, 50);
                   }
                   else
                   {
                       cout<<"Error in updateIndex->findConnection with startNode "<<startNode<<" goalNode "<<goalNode<<endl;
                       return FAIL;
                   }

               }
               else{
                   BFSresult = BBFS(Index, Buffer, startNode, Index_inv, Buffer_inv, goalNode, 50);
               }
                   cout<<"Path length is: "<<BFSresult<<endl;
                   BFSresult = 0;
                   numberOfQuestions++;
             }
// End of case Q -------------------------------------------------------------------------------------------------------
          }

// Getting new line from Workload FILE ---------------------------------------------------------------------------------
           getline(inpoutFile,inpout);
           strcpy(inpoutLine,inpout.c_str());
           part1=strtok(inpoutLine," \n\t");
// End of while statement starting next run-----------------------------------------------------------------------------
         }
// ----!!! Workload Finish !!!------------------------------------------------------------------------------------------
       }
// -------!!! Graph Creation starts here !!!!!--------------------------------------------------------------------------
       else{
         cout<< "GRAPH CREATION"<<endl;
// Initializing Graph structs ------------------------------------------------------------------------------------------
         Buffer = new buffer(BUFFER_SIZE,LIST_NODE_SIZE);
         Index = new n_index(INDEX_SIZE);
         Buffer_inv = new buffer(BUFFER_SIZE,LIST_NODE_SIZE);
         Index_inv = new n_index(INDEX_SIZE);

// Reading input from FILE - Insert data in Graph-----------------------------------------------------------------------
         while(strcmp(part1,"S")){
           strcpy(initial,part1);
           part1=strtok(NULL," \n\t");
           strcpy(part2,part1);

           if(Index->getEntry(atoi(initial))==INVALID){
           		int temp = Buffer->addListNode();
           		Index->addEntry(temp,atoi(initial));
           }

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
// End of while statement -- read new line for Graph insertion ---------------------------------------------------------
         }
         inpoutFile.close();
// End of Graph Insert -- Input FILE is closed--------------------------------------------------------------------------

// GCC call and test prints --------------------------------------------------------------------------------------------
           cout<<"Before Main call"<<endl;
           GetConnectedComponents(Index, Buffer, Index_inv, Buffer_inv);
           cout<<"After Main call"<<endl;

//         Index_inv->printCCnum(); // print outgoing Index: nodename -- offset -- CCnumber !!!
//           Index->printCCnum();     // print incoming Index: nodename -- offset -- CCnumber !!!
//         uint32_t* neighbors;
//         int k;
//         neighbors = Buffer->getNeighbors(k, Index->getEntry(1));
//         for (int i = 0; i < (k); i++){
//             cout<<"neighbors of 0 "<<neighbors[i]<<endl;
//         }
        cout<<"connected component count: "<<Index->getTotalConnectedComponents()<<endl;
// End of test prints --------------------------------------------------------------------------------------------------
       }
//---!!! Graph creation finished !!!!-----------------------------------------------------------------------------------

       cout<<"CHOOSE"<<endl<< "0 - QUIT"<<endl<<"OR"<<endl<< "1 - INSERT WORK FILE"<<endl;
       cin>>OPTION;
       if (OPTION == 0)
       {
         inpoutFile.close();
         cout << "EXITING" <<endl;
       }
  }while( OPTION == 1 ); // KEEP READING WORKLOAD FILE UNTIL TERMINATED BY 0 INPUT ------------------------------------

	cout<<"----- END OF MAIN()! -----"<<endl;
	return 0;
}
