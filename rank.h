//
// Created by Windows 8 on 10-Dec-16.
//

#ifndef PROJECTZAPDOS_RANK_H
#define PROJECTZAPDOS_RANK_H


#include "defines.h"

class g_rank {

private:
    int **table;
public:
    g_rank(int sizeOfGrail);

    virtual ~g_rank();

    int **getTable() const;

    void setTable(int **table);

    OK_SUCCESS insert(int minrank , int rank , int nodeName);

   OK_SUCCESS  askRank(int from ,int to);

   int getMinRank(int nodeName);
   OK_SUCCESS setMinRank(int nodeName, int minRank);

   int getRank(int nodeName);
   OK_SUCCESS setRank(int nodeName , int rank);
};


#endif //PROJECTZAPDOS_RANK_H
