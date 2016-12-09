//
// Created by Windows 8 on 07-Dec-16.
//
#include <iostream>

#include "updateIndex.h"
updateIndex::updateIndex() {
   table =(int**) malloc(UPDATE_INDEX_SIZE*sizeof(int*));
    for (int i = 0; i <UPDATE_INDEX_SIZE ; ++i) {
        table[i] = new int[2];
        table[i][FROM]=INVALID;
        table[i][TO]=INVALID;
    }
    this->metricValue = INVALID;
    this->latestEntry = 0;
}

updateIndex::~updateIndex() {
    for (int i = 0; i < UPDATE_INDEX_SIZE; i++){
        delete table[i];
    }
    free(table);
    std::cout<<"Update Index deleted"<<std::endl;
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

float updateIndex::calculateMetricValue(int totalQueries) {
    if(totalQueries > 0) return (float)metricValue / (float)totalQueries;
    return FAIL;
}

OK_SUCCESS updateIndex::addNewConnection(int from, int to) {
    if(from < 0 || to < 0) return FAIL;
    if(findConnection(from, to) == ALREADY_IN_UPDATE_INDEX)
    {
        return ALREADY_IN_UPDATE_INDEX;
    }
    else
    {
        this->table[this->latestEntry][FROM]=from;
        this->table[this->latestEntry][TO]=to;
        this->latestEntry++;
        return OK;
    }
}

OK_SUCCESS updateIndex::findConnection(int from, int to) {
    if(from < 0 || to < 0) return FAIL;
    for (int i = 0; i < this->latestEntry; i++) {
        if( (this->table[i][FROM] == from && this->table[i][TO] == to) || (this->table[i][FROM] == to && this->table[i][TO] == from) ) return ALREADY_IN_UPDATE_INDEX;
    }
    return NOT_IN_UPDATE_INDEX;
}

int updateIndex::getLatestEntry() const {
    return latestEntry;
}

void updateIndex::setLatestEntry(int latestEntry) {
    updateIndex::latestEntry = latestEntry;
}
