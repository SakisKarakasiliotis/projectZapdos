#include <iostream>
#include "updateIndex.h"
updateIndex::updateIndex() {
   table =(int**) malloc(UPDATE_INDEX_SIZE*sizeof(int*));
    size = UPDATE_INDEX_SIZE;
    for (int i = 0; i <UPDATE_INDEX_SIZE ; ++i) {
        table[i] = new int[3];
        table[i][FROM]=INVALID;
        table[i][TO]=INVALID;
        table[i][VERSION]=0;
    }
    this->metricValue = INVALID;
    this->latestEntry = 0;
}


updateIndex::~updateIndex() {
    for (int i = 0; i < size; i++){
        delete table[i];
    }
    free(table);
}

OK_SUCCESS updateIndex::resize() {
    table = (int**) realloc(table, 2*size*sizeof(int*));
    if(table == NULL) return FAIL;
    for (int i = size; i < 2*size; ++i) {
        table[i] = new int[3];
        table[i][FROM]=INVALID;
        table[i][TO]=INVALID;
        table[i][VERSION]=0;
    }
    size = 2*size;
    return OK;
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
OK_SUCCESS updateIndex::addNewConnection(int from, int to, int version) {
    int resize_result;
    if(from < 0 || to < 0) return FAIL;
    if(latestEntry == size) resize_result = resize();
    if(resize_result == FAIL) return FAIL;
    if(findConnection(from, to, version) == ALREADY_IN_UPDATE_INDEX)
    {
        return ALREADY_IN_UPDATE_INDEX;
    }
    else
    {
        this->table[this->latestEntry][FROM]=from;
        this->table[this->latestEntry][TO]=to;
        this->table[this->latestEntry][VERSION]=version;
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

OK_SUCCESS updateIndex::findConnection(int from, int to, int version) {
    if(from < 0 || to < 0 || version < 0) return FAIL;
    for (int i = 0; i < this->latestEntry; i++) {
        if( ( (this->table[i][FROM] == from && this->table[i][TO] == to) || (this->table[i][FROM] == to && this->table[i][TO] == from) ) && this->table[i][VERSION] == version ) return ALREADY_IN_UPDATE_INDEX;
    }
    return NOT_IN_UPDATE_INDEX;
}

int updateIndex::getLatestEntry() const {
    return latestEntry;
}

void updateIndex::setLatestEntry(int latestEntry) {
    updateIndex::latestEntry = latestEntry;
}
