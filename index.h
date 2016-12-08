#ifndef INDEX_H
#define INDEX_H
#include "defines.h"

class n_index{
  private:
    int* offsets;
    int* CCnum;
    int numberOfEntries;
    int sizeOfIndex;
    int totalConnectedComponents; // contains the id of the Connected component to be allocated next !! remember to increase by 1 on each use !!!!!!
public:
    int getTotalConnectedComponents() const;

    void setTotalConnectedComponents(int totalConnectedComponents);

public:
    n_index(int size);
    ~n_index();
    OK_SUCCESS setNumberOfEntries(int numberOfEntries);
    int getNumberOfEntries();
    OK_SUCCESS setSizeOfIndex(int sizeOfIndex);
    int getSizeOfIndex();
    OK_SUCCESS addEntry(int entryOffset,int nodeName);
    int getEntry(int entryNumber);
    //modes are 1:double 2:resize to newsize 3:multiply with newsize //
    OK_SUCCESS resize(int newsize,int mode);
    //returns CCnum of node. If invalid not yet set
    int getCCnum(int nodeName);
    OK_SUCCESS setCCnum(uint32_t nodeName, int CCname);
    void printCCnum();
};

#endif
