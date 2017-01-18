#include <iostream>
#include <cstdlib>
#include <cstdio>

#include "job.h"
//#include "staticBFS.h"

staticJob :: staticJob(int id, int start, int goal){
   this->ID = id;
   this->startNode = start;
   this->goalNode = goal;
}
staticJob :: ~staticJob(){
   cout<<"job: "<<this->ID<<" finished"<<endl;
}

int staticJob :: executeQuery(){
   printf("Executing job No %d.\n", this->ID);
}