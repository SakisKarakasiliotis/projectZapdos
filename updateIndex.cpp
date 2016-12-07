//
// Created by Windows 8 on 07-Dec-16.
//

#include "updateIndex.h"

updateIndex::updateIndex() {
   table =(int**) malloc(UPDATE_INDEX_SIZE*sizeof(int*));
    for (int i = 0; i <UPDATE_INDEX_SIZE ; ++i) {
        table[i] = new int[2];
        table[i][0]=INVALID;
        table[i][1]=INVALID;
    }
    this->metricValue = INVALID;
}

updateIndex::~updateIndex() {

}

int updateIndex::getMetricValue() const {
    return metricValue;
}

void updateIndex::setMetricValue(int metricValue) {
    updateIndex::metricValue = metricValue;
}

int **updateIndex::getTable() const {
    return table;
}

void updateIndex::setTable(int **table) {
    updateIndex::table = table;
}
