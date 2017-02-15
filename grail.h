#ifndef PROJECTZAPDOS_GRAIL_H
#define PROJECTZAPDOS_GRAIL_H

#include <iostream>
#include "index.h"
#include "buffer.h"
#include "stronglyConnectedComponents.h"
#include "rank.h"


typedef struct{
    component* component_ptr;
    int currentID;
} componentCursor;


class grail {
private:
    n_index* index;
    g_rank *ranks;
    int sizeOfGrail; // number of SCC
    buffer* g_buffer;
    stronglyConnectedComponents* SCC;

public:
    grail();

    stronglyConnectedComponents *getSCC() const;

    void setSCC(stronglyConnectedComponents *SCC);

    buffer *getG_buffer() const;

    void setG_buffer(buffer *g_buffer);

    ~grail();

    n_index *getIndex() const;

    void setIndex(n_index *index);


    int getSizeOfGrail() const;

    void setSizeOfGrail(int sizeOfGrail);

    OK_SUCCESS calculateSCC(n_index* subGraphIndex, n_index* subGraphIndexInv, buffer* subGraphBuffer);

    OK_SUCCESS initializeGrail();

    OK_SUCCESS generateHyperGraph(n_index *subGraphIndex, buffer *subGraphBuffer);

    OK_SUCCESS calculateRanks();

    OK_SUCCESS askGrail(int from , int to);

   int getSCCId(int nodeName);
    OK_SUCCESS iterateStronglyConnectedComponentID(componentCursor* cursor);
    bool next_StronglyConnectedComponentID(componentCursor* cursor);
};

class tarjanNode{
public:
   tarjanNode(int nodeName);
   ~tarjanNode();

   int getNodeName() const;

   void setNodeName(int nodeName);

   int getTIndex() const;

   void setTIndex(int tIndex);

   int getLowlink() const;

   void setLowlink(int lowlink);

   bool isDFSInitialized() const;

   void setDFSInitialized(bool DFSInitialized);

private:
   int nodeName;
   int tIndex;
   int lowlink;
   bool DFSInitialized;
};


#endif //PROJECTZAPDOS_GRAIL_H
