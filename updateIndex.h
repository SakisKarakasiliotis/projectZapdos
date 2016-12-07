//
// Created by Windows 8 on 07-Dec-16.
//

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

private:
        int **table;
        int metricValue;
};


#endif //PROJECTZAPDOSCLION_UPDATEINDEX_H
