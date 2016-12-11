//
// Created by Windows 8 on 10-Dec-16.
//

#include <stdlib.h>
#include "rank.h"
#include "defines.h"

int **rank::getTable() const {
    return table;
}

void rank::setTable(int **table) {
    rank::table = table;
}

rank::rank(int sizeOfGrail) {
    table =(int**) malloc(sizeOfGrail*sizeof(int*));
    for (int i = 0; i <sizeOfGrail ; i++) {
        table[i] = new int[2];
        table[i][MIN_RANK]=INVALID;
        table[i][RANK]=INVALID;
    }
}

rank::~rank() {

}

OK_SUCCESS rank::insert(int minrank, int rank, int nodeName){
   if(nodeName<0 || rank < 0 || minrank < 0 || minrank > rank){
      return FAIL;
   }
   this->table[nodeName][MIN_RANK]= minrank;
   this->table[nodeName][RANK]= rank;
   return OK;
}

OK_SUCCESS rank::askRank(int from, int to) {
   int from_min_rank = this->table[from][MIN_RANK];
   int from_rank = this->table[from][RANK];
   int to_min_rank = this->table[to][MIN_RANK];
   int to_rank = this->table[to][RANK];
   
   if( to_min_rank >= from_min_rank && to_rank <= from_rank ) return MAYBE;
   return NO;
}

int rank::getMinRank(int nodeName) {
   if(nodeName<0){
      return FAIL;
   }
   return this->table[nodeName][MIN_RANK];
}

int rank::getRank(int nodeName) {
   if(nodeName<0){
      return FAIL;
   }
   return this->table[nodeName][RANK];
}

OK_SUCCESS rank::setMinRank(int nodeName, int minRank) {
   if(nodeName < 0 || minRank < 0){
      return FAIL;
   }
   this->table[nodeName][MIN_RANK]= minRank;
   return OK;
}

OK_SUCCESS rank::setRank(int nodeName, int rank) {
   if(nodeName<0 || rank<0){
      return FAIL;
   }
   this->table[nodeName][RANK] = rank;
   return OK;
}
