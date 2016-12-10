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
