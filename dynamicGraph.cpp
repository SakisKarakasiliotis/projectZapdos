//
// Created by Marcus on 11/12/2016.
//
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>

#include "defines.h"
#include "list_node.h"
#include "myHash.h"
#include "buffer.h"
#include "index.h"
#include "bfs.h"
#include "updateIndex.h"
#include "dynamicGraph.h"
#include "scheduler.h"
#include "job.h"

int dynamicGraph() {
//FILE READING VARIABLES -----------------------------------------------------------------------------------------------
   string inpout;
   char *part1,part2[80],part3[80],initial[80],get[600];
   ifstream inpoutFile;
   string in;
   char inpoutLine[80]={0};
   char hashLine[80];
//GRAPH VARIABLES ------------------------------------------------------------------------------------------------------
   buffer* Buffer ;
   n_index* Index ;
   buffer* Buffer_inv ;
   n_index* Index_inv ;
   updateIndex* update_index = new updateIndex();
   hashClass* indexHash = new hashClass(HASH_SIZE, HASH_PERCISION);
//HELPERS --------------------------------------------------------------------------------------------------------------
   int entry=0, lineNumber=0, OPTION=2,entry_inv=0, numberOfQuestions=0, versionIter = 0 , currentJobID = 0, ui_result;
//JOB AND SCHEDLER VARIABLES -------------------------------------------------------------------------------------------
   JobScheduler* manager;

//START READING FILES FOR GRAPH CREATION--------------------------------------------------------------------------------
   cout<<"INSERT ENTRY FILE: "<<endl;
   do{
      //TODO: SELECT PATH ACCORDING TO FILE REQUIRED !!!!!!!
      if(OPTION==1){
//          strcpy(get, "/media/sf_projectZapdosClion/tiny2/tinyWorkload_FINAL.txt");
          strcpy(get, "/media/sf_projectZapdosClion/small2/smallWorkload_FINAL.txt");

      }
      else{
//         strcpy(get,"/media/sf_projectZapdosClion/tiny2/tinyGraph.txt");
         strcpy(get,"/media/sf_projectZapdosClion/small2/smallGraph.txt");

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
          manager = new JobScheduler(THREAD_NUMBER);
          while(!strcmp(part1,"A")||!strcmp(part1,"Q")||!strcmp(part1, "F")){
            if(strcmp(part1,"F")){
               strcpy(initial,part1);
               part1=strtok(NULL," \n\t");
               strcpy(part2,part1);
               part1=strtok(NULL," \n\t");
               strcpy(part3,part1);
// Case A adding entry to Graph-----------------------------------------------------------------------------------------
               if(!strcmp(initial,"A")){
                  cout<< "ADDING TO GRAPH" <<endl;
                  strcpy(hashLine,inpout.substr(2).c_str());
                  if (indexHash->checkHash(hashLine)) {
//                     cout << "Input \"" << hashLine <<"\" has been found before!" << endl;
                  }
                  else {
//                     cout << "Input \"" << hashLine <<"\" was hashed successfully!" << endl;
                     int startNode = atoi(part2);
                     int goalNode = atoi(part3);
// Updating outgoing Index ---------------------------------------------------------------------------------------------
                     entry = Index->getEntry(startNode);
                     if(entry == FAIL){
                        cout<<"OUT OF BOUNDS on Index entry "<<startNode<<" and "<<goalNode<<endl;
                        return FAIL;
                     }
                     else if(entry == INVALID){
                        int temp = Buffer->addListNode();
                        Index->addEntry(temp,startNode);
                        Buffer->insertNeighbor(Index->getEntry(startNode), goalNode, versionIter);
                        int possibleCCnum = Index->getCCnum(goalNode);
                        if(possibleCCnum == FAIL) {
                           cout<<"Requested Node "<<goalNode<<" is out of bounds on getccnum"<<endl;
                           return FAIL;
                        }
                        if( possibleCCnum != INVALID )
                        {
                           Index->setCCnum(startNode, possibleCCnum);
                        }
                        else
                        {
                           possibleCCnum = Index->getTotalConnectedComponents();
                           Index->setTotalConnectedComponents(Index->getTotalConnectedComponents()+1);
                           Index->setCCnum(goalNode, possibleCCnum);
                           Index->setCCnum(startNode, possibleCCnum);
                        }
                     }
                     else if(entry!=INVALID){
                        Buffer->insertNeighbor(Index->getEntry(startNode),goalNode, versionIter);
                        int possibleCCnum = Index->getCCnum(startNode);
                        if(possibleCCnum == FAIL){
                           cout<<"Requested Node "<<startNode<<" is out of bounds on getccnum"<<endl;
                           return FAIL;
                        }
                        if(possibleCCnum == INVALID){
                           possibleCCnum = Index->getCCnum(goalNode);
                           if( possibleCCnum != INVALID){
                              Index->setCCnum(startNode, possibleCCnum);
                           }
                           else{
                              possibleCCnum = Index->getTotalConnectedComponents();
                              Index->setTotalConnectedComponents(Index->getTotalConnectedComponents()+1);
                              Index->setCCnum(goalNode, possibleCCnum);
                              Index->setCCnum(startNode, possibleCCnum);
                           }
                        }
                        else{
                           int goalNodeCCnum = Index->getCCnum(goalNode);
                           if(goalNodeCCnum == INVALID){
                              Index->setCCnum(goalNode,possibleCCnum);
                           }
                           else{
                              if(possibleCCnum != goalNodeCCnum){
                                 int foundInUpdateIndex = update_index->findConnection(possibleCCnum,goalNodeCCnum, versionIter);
                                 if(foundInUpdateIndex == NOT_IN_UPDATE_INDEX){
                                     ui_result = update_index->addNewConnection(possibleCCnum,goalNodeCCnum, versionIter);
                                     if(ui_result == FAIL){
                                         cout<<"Something went wrong with ui"<<endl;
                                     }
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
                     entry_inv = Index_inv->getEntry(goalNode);
                     if(entry_inv == FAIL){
                        cout<<"OUT OF BOUNDS on Inverted Index entry "<<startNode<<" and "<<goalNode<<endl;
                        return FAIL;
                     }
                     else if(entry_inv == INVALID){
                        int temp_inv = Buffer_inv->addListNode();
                        Index_inv->addEntry(temp_inv,goalNode);
                        Buffer_inv->insertNeighbor(Index_inv->getEntry(goalNode),startNode, versionIter);
                     }
                     else if(entry_inv!=INVALID){
                        Buffer_inv->insertNeighbor(Index_inv->getEntry(goalNode),startNode, versionIter);
                     }
                  }
// End of case A -------------------------------------------------------------------------------------------------------
               }

// Case Q for question on the graph ------------------------------------------------------------------------------------
               else if(!strcmp(initial,"Q")){

                  cout<<"Question "<<numberOfQuestions<<":"<<endl;
                  int startNode = atoi(part2);
                  int goalNode = atoi(part3);
                    dynamicJob* newJob = new dynamicJob(currentJobID, startNode, goalNode, Index, Buffer, Index_inv, Buffer_inv, versionIter , update_index);
                    currentJobID++;
                    cout<<"About to enqueue a new job"<<endl;
                    string res;
                    if(manager->submit_job(newJob)){
                        res = "true";
                    } else {
                        res = "false";
                    }
                    cout<<res<<endl;

//                  if( Index->getCCnum(startNode) != Index->getCCnum(goalNode) ){
//                     int hasUpdateConnection = update_index->findConnection( Index->getCCnum(startNode), Index->getCCnum(goalNode) );
//                     if( hasUpdateConnection == NOT_IN_UPDATE_INDEX )
//                     {
//                        cout<<"No path between "<<startNode<<" and "<<goalNode<<endl;
//                        BFSresult = INVALID;
//                     }
//                     else if(hasUpdateConnection == ALREADY_IN_UPDATE_INDEX)
//                     {
////                        BFSresult = BBFS(Index, Buffer, startNode, Index_inv, Buffer_inv, goalNode, BFS_FRINGE_SIZE);
////                        BFSresult = DBBFS(Index, Buffer, startNode, Index_inv, Buffer_inv, goalNode, BFS_FRINGE_SIZE, 0);
//                        int numberOfNeighbors;
//                         uint32_t* neighbors = Buffer->getNeighbors(numberOfNeighbors, Index->getEntry(3), 0);
//                         cout << "neighbors of " << goalNode <<":" <<endl;
//                         for (int i=0; i<numberOfNeighbors; i++) {
//                             cout << neighbors[i] << endl;
//                         }
//                     }
//                     else
//                     {
//                        cout<<"Error in updateIndex->findConnection with startNode "<<startNode<<" goalNode "<<goalNode<<endl;
//                        return FAIL;
//                     }
//                     update_index->setMetricValue(update_index->getMetricValue()+1);
//                  }
//                  else{
//                      int numberOfNeighbors;
//                      uint32_t* neighbors = Buffer->getNeighbors(numberOfNeighbors, Index->getEntry(3), 0);
//                      cout << "neighbors of " << goalNode <<" (version sensitive):" <<endl;
//                      for (int i=0; i<numberOfNeighbors; i++) {
//                          cout << neighbors[i] << endl;
//                      }
//                      neighbors = Buffer->getNeighbors(numberOfNeighbors, Index->getEntry(3));
//                      cout << "neighbors of " << goalNode <<":" <<endl;
//                      for (int i=0; i<numberOfNeighbors; i++) {
//                          cout << neighbors[i] << endl;
//                      }
////                     BFSresult = BBFS(Index, Buffer, startNode, Index_inv, Buffer_inv, goalNode, BFS_FRINGE_SIZE);
//                  }
//                  cout<<"Path length is: "<<BFSresult<<endl;
//                  BFSresult = 0;
//                  numberOfQuestions++;
               }
// End of case Q -------------------------------------------------------------------------------------------------------
            }
            else if(!strcmp(part1,"F"))
// Case F start --------------------------------------------------------------------------------------------------------
            {
               manager->execute_all_jobs();
               manager->wait_all_tasks_finish();
               int x;
               cout << "Press any key to run next batch" << endl;
               cin >> x;
               if(update_index->calculateMetricValue(numberOfQuestions) >= RECALCULATE_CONECTED_COMPONENTS){
                  for( int i=0; i<Index->getSizeOfIndex(); i++){
                     Index->setCCnum(i, INVALID);
                     Index_inv->setCCnum(i, INVALID);
                  }
                  delete update_index;
                  GetConnectedComponents(Index, Buffer, Index_inv, Buffer_inv);
                  update_index = new updateIndex();

               }
               numberOfQuestions = 0;
               currentJobID = 0;
// End of case F -------------------------------------------------------------------------------------------------------
            }

// Getting new line from Workload FILE ---------------------------------------------------------------------------------
            getline(inpoutFile,inpout);
            if(!inpoutFile.eof()){
               strcpy(inpoutLine,inpout.c_str());
               part1=strtok(inpoutLine," \n\t");
               if(!strcmp(part1,"A") && !strcmp(initial,"Q")){
                   versionIter++;
               }
            }
            else{
               strcpy(part1,"done");
            }
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
            strcpy(hashLine,inpout.c_str());
            if (indexHash->checkHash(hashLine)) {
//               cout << "ATTENTION! Inpput \"" << hashLine << "\" has been found before!" << endl;
            }
            else {
//               cout << "Inpput \"" << hashLine << "\" was hashed successfully!" << endl;
            }
            part1=strtok(NULL," \n\t");
            strcpy(part2,part1);
            int startNode = atoi(initial);
            int goalNode = atoi(part2);

            if(Index->getEntry(startNode)==INVALID){
               int temp = Buffer->addListNode();
               Index->addEntry(temp,startNode);
            }

            Buffer->insertNeighbor(Index->getEntry(startNode),goalNode, 0);

            if(Index_inv->getEntry(goalNode)==INVALID){
               int temp_inv = Buffer_inv->addListNode();
               Index_inv->addEntry(temp_inv,goalNode);
            }

            Buffer_inv->insertNeighbor(Index_inv->getEntry(goalNode),startNode, 0);
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