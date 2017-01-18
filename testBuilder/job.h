#ifndef JOB_H
#define JOB_H

#include "defines.h"
// #include "index.h"
// #include "buffer.h"
// #include "grail.h"

class job {
protected:
   int ID;
   int startNode;
   int goalNode;
   
public:
   int getID();
   OK_SUCCESS setID(int ID);

  int getStartNode();
  OK_SUCCESS setStartNode(int node);

  int getGoalNode();
  OK_SUCCESS setGoalNode(int node);
   
  // virtual int executeQuery(grail* holy, n_index* outIndex, buffer* outgoing, n_index* inIndex, buffer* incoming) = 0;
   virtual int executeQuery() = 0;
};

class dynamicJob: public job{
private:
   int version;
public:
   dynamicJob(int id, int start, int goal);
   ~dynamicJob();

   int getVersion();
   OK_SUCCESS setVersion(int ver);

 //  int executeQuery(grail* holy, n_index* outIndex, buffer* outgoing, n_index* inIndex, buffer* incoming);
   int executeQuery();
};

class staticJob: public job{
public:
   staticJob(int id, int start, int goal);
   ~staticJob();

  // int executeQuery(grail* holy, n_index* outIndex, buffer* outgoing, n_index* inIndex, buffer* incoming);
   int executeQuery();
};

#endif