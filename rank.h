//
// Created by Windows 8 on 10-Dec-16.
//

#ifndef PROJECTZAPDOS_RANK_H
#define PROJECTZAPDOS_RANK_H


class rank {

private:
    int **table;
public:
    rank(int sizeOfGrail);

    virtual ~rank();

    int **getTable() const;

    void setTable(int **table);
};


#endif //PROJECTZAPDOS_RANK_H
