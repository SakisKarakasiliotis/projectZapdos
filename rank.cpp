#include <stdlib.h>
#include "rank.h"
#include "defines.h"

int **g_rank::getTable() const {
    return table;
}

void g_rank::setTable(int **table) {
    g_rank::table = table;
}

g_rank::g_rank(int sizeOfGrail) {
    table =(int**) malloc(sizeOfGrail*sizeof(int*));
    for (int i = 0; i <sizeOfGrail ; i++) {
        table[i] = new int[2];
        table[i][MIN_RANK]=INVALID;
        table[i][RANK]=INVALID;
    }
}

g_rank::~g_rank() {

}

OK_SUCCESS g_rank::insert(int minrank, int rank, int nodeName){
   if(nodeName<0 || rank < 0 || minrank < 0 || minrank > rank){
      return FAIL;
   }
   this->table[nodeName][MIN_RANK]= minrank;
   this->table[nodeName][RANK]= rank;
   return OK;
}

OK_SUCCESS g_rank::askRank(int from, int to) {
   int from_min_rank = this->table[from][MIN_RANK];
   int from_rank = this->table[from][RANK];
   int to_min_rank = this->table[to][MIN_RANK];
   int to_rank = this->table[to][RANK];

   if( to_min_rank >= from_min_rank && to_rank <= from_rank ) return MAYBE;
   return NO;
}

int g_rank::getMinRank(int nodeName) {
   if(nodeName<0){
      return FAIL;
   }
   return this->table[nodeName][MIN_RANK];
}

int g_rank::getRank(int nodeName) {
   if(nodeName<0){
      return FAIL;
   }
   return this->table[nodeName][RANK];
}

OK_SUCCESS g_rank::setMinRank(int nodeName, int minRank) {
   if(nodeName < 0 || minRank < 0){
      return FAIL;
   }
   this->table[nodeName][MIN_RANK]= minRank;
   return OK;
}

OK_SUCCESS g_rank::setRank(int nodeName, int rank) {
   if(nodeName<0 || rank<0){
      return FAIL;
   }
   this->table[nodeName][RANK] = rank;
   return OK;
}
