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
   do{
      if(OPTION==1){
//          strcpy(get, "/media/sf_projectZapdosClion/tiny2/tinyWorkload_FINAL.txt");
         strcpy(get, "/media/sf_projectZapdosClion/medium2/mediumWorkload_FINAL.txt");

      }
      else{
//         strcpy(get,"/media/sf_projectZapdosClion/tiny2/tinyGraph.txt");
         strcpy(get,"/media/sf_projectZapdosClion/medium2/mediumGraph.txt");

      }

// Initializing FILE getting first token--------------------------------------------------------------------------------
      inpoutFile.open(get);
      getline(inpoutFile,inpout);
      strcpy(inpoutLine,inpout.c_str());
      part1= strtok(inpoutLine," \n\t");
// Token selected check for case Addition/Question or Creation----------------------------------------------------------


// -------!!! Graph Creation starts here !!!!!--------------------------------------------------------------------------
      if (OPTION != 1) {
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
// End of Graph Insert -- Input FILE is closed--------------------------------------------------------------------------

// Grail call and test prints --------------------------------------------------------------------------------------------
         if (goblet->calculateSCC(Index, Index_inv, Buffer) != OK) {
            cout << "calculateSCC failed!" << endl;
            return FAIL;
         }
         if (goblet->initializeGrail() != OK) {
            cout << "initializeGrail failed!" << endl;
            return FAIL;
         }
         if (goblet->generateHyperGraph(Index, Buffer) != OK) {
            cout << "generateHyperGraph failed!" << endl;
            return FAIL;
         }
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
                     int startNode = atoi(part2);
                     int goalNode = atoi(part3);
                     staticJob* newJob = new staticJob(currentJobID, startNode, goalNode, goblet, Index, Buffer, Index_inv, Buffer_inv);
                     currentJobID++;
                     manager->submit_job(newJob);
                     numberOfQuestions++;
                  }
// End of case Q -------------------------------------------------------------------------------------------------------
               }
               else if(!strcmp(part1,"F"))
// Case F start --------------------------------------------------------------------------------------------------------
               {
                 manager->execute_all_jobs();
                 currentJobID = 0;
                 manager->wait_all_tasks_finish();
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

