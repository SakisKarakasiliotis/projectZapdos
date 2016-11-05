#ifndef INDEX_H
#define INDEX_H
#include "defines.h"

class index{
  private:
    int* offsets;
    int numberOfEntries;
    int sizeOfIndex;
  public:
    index(int size);
    ~index();
    OK_SUCCESS setNumberOfEntries(int numberOfEntries);
    int getNumberOfEntries();
    OK_SUCCESS setSizeOfIndex(int sizeOfIndex);
    int getSizeOfIndex();
    OK_SUCCESS addEntry(int entryOffset,int nodeName);
    int getEntry(int entryNumber);
    //modes are 1:double 2:resize to newsize 3:multiply with newsize //
    OK_SUCCESS resize(int newsize,int mode);
};

#endif
