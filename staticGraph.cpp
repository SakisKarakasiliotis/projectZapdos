//
// Created by Marcus on 11/12/2016.
//
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <getopt.h>

#include "defines.h"
#include "list_node.h"
#include "buffer.h"
#include "index.h"
#include "staticBfs.h"
#include "grail.h"
#include "staticGraph.h"
#include "job.h"
#include "scheduler.h"

//DLETE THOSE
#include "bfs.h"
#include "updateIndex.h"

int staticGraph() {
   //FILE READING VARIABLES --------------------------------------------------------------------------------------------
   string inpout;
   char *part1,part2[80],part3[80],initial[80],get[600];
   ifstream inpoutFile;
   string in;
   char inpoutLine[80]={0};
   grail* goblet;
//GRAPH VARIABLES ------------------------------------------------------------------------------------------------------
   buffer* Buffer ;
   n_index* Index ;
   buffer* Buffer_inv ;
   n_index* Index_inv ;
//HELPERS --------------------------------------------------------------------------------------------------------------
   int entry=0, lineNumber=0, OPTION=2,entry_inv=0, numberOfQuestions=0, BFSresult, currentJobID = 0;
//JOB AND SCHEDLER VARIABLES -------------------------------------------------------------------------------------------
   JobScheduler* manager;


//START READING FILES FOR GRAPH CREATION--------------------------------------------------------------------------------
   cout<<"INSERT ENTRY FILE: "<<endl;
   do{
      //TODO: SELECT PATH ACCORDING TO FILE REQUIRED !!!!!!!
      if(OPTION==1){//WORKLOAD
          strcpy(get, "/media/sf_projectZapdosClion/small2/smallWorkload_FINAL.txt");
//          strcpy(get, "/media/sf_projectZapdosClion/tiny2/tinyWorkload_FINAL.txt");
//          strcpy(get, "/media/sf_projectZapdosClion/tiny2/tinyWorkload_FINAL.txt");
//          strcpy(get, "/media/sf_projectZapdosClion/b.txt");
//          strcpy(get, "/media/sf_projectZapdosClion/wikigraph/wikigraph_work.txt");
      }
      else{//GRAPH
         strcpy(get,"/media/sf_projectZapdosClion/small2/smallGraph.txt");
//         strcpy(get,"/media/sf_projectZapdosClion/tiny2/tinyGraph.txt");
//         strcpy(get,"/media/sf_projectZapdosClion/a.txt");
//         strcpy(get,"/media/sf_projectZapdosClion/wikigraph/wikigraph.txt");

      }

// Initializing FILE getting first token--------------------------------------------------------------------------------
      inpoutFile.open(get);
      getline(inpoutFile,inpout);
      strcpy(inpoutLine,inpout.c_str());
      part1= strtok(inpoutLine," \n\t");
      cout<<"FIRST LINE "<<lineNumber<<" TOKEN: "<<part1<<endl;

// Token selected check for case Addition/Question or Creation----------------------------------------------------------


// -------!!! Graph Creation starts here !!!!!--------------------------------------------------------------------------
      if (OPTION != 1) {
         cout<< "GRAPH CREATION"<<endl;
// Initializing Graph structs ------------------------------------------------------------------------------------------
         Buffer = new buffer(BUFFER_SIZE,LIST_NODE_SIZE);
         Index = new n_index(INDEX_SIZE);
         Buffer_inv = new buffer(BUFFER_SIZE,LIST_NODE_SIZE);
         Index_inv = new n_index(INDEX_SIZE);
         goblet = new grail();
// Reading input from FILE - Insert data in Graph-----------------------------------------------------------------------

         while(strcmp(part1,"S")){
            strcpy(initial,part1);
            part1=strtok(NULL," \n\t");
            strcpy(part2,part1);
            int startNode = atoi(initial);
            int goalNode = atoi(part2);

            if(Index->getEntry(startNode)==INVALID){
               int temp = Buffer->addListNode();
               Index->addEntry(temp,startNode);
            }

            Buffer->insertNeighbor(Index->getEntry(startNode),goalNode);

            if(Index_inv->getEntry(goalNode)==INVALID){
               int temp_inv = Buffer_inv->addListNode();
               Index_inv->addEntry(temp_inv,goalNode);
            }

            Buffer_inv->insertNeighbor(Index_inv->getEntry(goalNode),startNode);
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
                     cout<<"i m there"<<endl;

// End of Graph Insert -- Input FILE is closed--------------------------------------------------------------------------

// Grail call and test prints --------------------------------------------------------------------------------------------
         cout << "Calculating SCC" << endl;
         if (goblet->calculateSCC(Index, Index_inv, Buffer) != OK) {
            cout << "calculateSCC failed!" << endl;
            return FAIL;
         }
//          Index->printGraph(Buffer);

         cout << "Initializing grail" << endl;
         if (goblet->initializeGrail() != OK) {
            cout << "initializeGrail failed!" << endl;
            return FAIL;
         }
         cout << "Generating hypergraph" << endl;
         if (goblet->generateHyperGraph(Index, Buffer) != OK) {
            cout << "generateHyperGraph failed!" << endl;
            return FAIL;
         }
         cout << "Calculating ranks" << endl;
         if (goblet->calculateRanks() != OK) {
            cout << "calculateRanks failed!" << endl;
            return FAIL;
         }
// End of test prints --------------------------------------------------------------------------------------------------
      }
//---!!! Graph creation finished !!!!-----------------------------------------------------------------------------------
      else{
         manager = new JobScheduler(THREAD_NUMBER);
         if(!strcmp(part1,"A")||!strcmp(part1,"Q")){
// -------------!! Workload execution started !!!----------------------------------------------------------------------
            cout<<"WORK FILE"<<endl;
            while(!strcmp(part1,"A")||!strcmp(part1,"Q")||!strcmp(part1, "F")){
               if(strcmp(part1,"F")){

                  strcpy(initial,part1);
                  part1=strtok(NULL," \n\t");
                  strcpy(part2,part1);
                  part1=strtok(NULL," \n\t");
                  strcpy(part3,part1);
// Case A adding entry to Graph-----------------------------------------------------------------------------------------

// End of case A -------------------------------------------------------------------------------------------------------

// Case Q for question on the graph ------------------------------------------------------------------------------------
                  if(!strcmp(initial,"Q")){
                     cout<<"Question "<<numberOfQuestions<<":"<<endl;
                     int startNode = atoi(part2);
                     int goalNode = atoi(part3);
                     staticJob* newJob = new staticJob(currentJobID, startNode, goalNode, goblet, Index, Buffer, Index_inv, Buffer_inv);
                     currentJobID++;
                     cout<<"About to enqueue a new job"<<endl;
                     string res;
                     if(manager->submit_job(newJob)){
                        res = "true";
                     } else {
                        res = "false";
                     }
                     cout<<res<<endl;
//                     if( Index->getCCnum(startNode) != Index->getCCnum(goalNode) ){
//                        if( hasUpdateConnection == NOT_IN_UPDATE_INDEX )
//                        {
//                           cout<<"No path between "<<startNode<<" and "<<goalNode<<endl;
//                           BFSresult = INVALID;
//                        }
//                        else if(hasUpdateConnection == ALREADY_IN_UPDATE_INDEX)
//                        {
//                           BFSresult = BBFS(Index, Buffer, startNode, Index_inv, Buffer_inv, goalNode, 50);
//                        }
//                        else
//                        {
//                           cout<<"Error in updateIndex->findConnection with startNode "<<startNode<<" goalNode "<<goalNode<<endl;
//                           return FAIL;
//                        }
//                     }
//                     else{
//                        BFSresult = BBFS(Index, Buffer, startNode, Index_inv, Buffer_inv, goalNode, 50);
//                     }

                    numberOfQuestions++;
                  }
// End of case Q -------------------------------------------------------------------------------------------------------
               }
               else if(!strcmp(part1,"F"))
// Case F start --------------------------------------------------------------------------------------------------------
               {
                 cout << "About to execute all jobs" << endl;
//                 manager->printQueue();
                 manager->execute_all_jobs();
                 manager->wait_all_tasks_finish();
                 int x;
                 cout << "Press any key to run next batch" << endl;
                 cin >> x;
//                  if(update_index->calculateMetricValue(numberOfQuestions) >= RECALCULATE_CONECTED_COMPONENTS){
//                     for( int i=0; i<Index->getSizeOfIndex(); i++){
//                        Index->setCCnum(i, INVALID);
//                        Index_inv->setCCnum(i, INVALID);
//                     }
//                     delete update_index;
//                     GetConnectedComponents(Index, Buffer, Index_inv, Buffer_inv);
//                     update_index = new updateIndex();
//
//                  }
//                  numberOfQuestions = 0;
// End of case F -------------------------------------------------------------------------------------------------------
               }

// Getting new line from Workload FILE ---------------------------------------------------------------------------------
               getline(inpoutFile,inpout);
               if(!inpoutFile.eof()){
                  strcpy(inpoutLine,inpout.c_str());
                  part1=strtok(inpoutLine," \n\t");
               }
               else{
                  strcpy(part1,"done");
               }
// End of while statement starting next run-----------------------------------------------------------------------------
            }
// ----!!! Workload Finish !!!------------------------------------------------------------------------------------------
         }
      }
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

