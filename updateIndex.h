
#ifndef PROJECTZAPDOSCLION_UPDATEINDEX_H
#define PROJECTZAPDOSCLION_UPDATEINDEX_H

#include "defines.h"

class updateIndex {
public:
    updateIndex();

    virtual ~updateIndex();

    int getMetricValue() const;

    void setMetricValue(int metricValue);

    int **getTable() const;

    void setTable(int **table);

    float calculateMetricValue(int);

    OK_SUCCESS resize();

    OK_SUCCESS addNewConnection(int, int);
    OK_SUCCESS addNewConnection(int, int, int);

    OK_SUCCESS findConnection(int, int);
    OK_SUCCESS findConnection(int, int, int);

private:
        int **table;
        int metricValue;
        int latestEntry;
        int size;
public:
    int getLatestEntry() const;

    void setLatestEntry(int latestEntry);
};


#endif //PROJECTZAPDOSCLION_UPDATEINDEX_H
