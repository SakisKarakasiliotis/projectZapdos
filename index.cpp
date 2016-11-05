#include <iostream>
#include "index.h"

index::index(int size){
  this->sizeOfIndex = size;
  this->offsets = (int*) malloc(this->sizeOfIndex);
  this->numberOfEntries = 0;
  for (int i = 0; i < size; i++) {
    offsets[i]= INVALID;
  }
}
index::~index(){
  free(this->offsets);
  this->sizeOfIndex = INVALID;
  this->numberOfEntries =0;
  cout << "deleting index"<<endl;
}
OK_SUCCESS index::setNumberOfEntries(int numberOfEntries){
  this->numberOfEntries = numberOfEntries;
  return OK;
}
int index::getNumberOfEntries(){
  return this->numberOfEntries;
}
OK_SUCCESS index::setSizeOfIndex(int sizeOfIndex){
  this->sizeOfIndex = sizeOfIndex;
  return OK;
}
int index::getSizeOfIndex(){
  return this->sizeOfIndex;
}
OK_SUCCESS index::addEntry(int entryOffset , int nodeName){
  if(nodeName > this->sizeOfIndex) {
    if(nodeName>2*this->sizeOfIndex){
      if(this->resize(nodeName,2)== FAIL){
        cout<<"unable to realloc from add entry mode 2 on node: "<< nodeName<<endl;
        return FAIL;
      }
    }
    else {
      if(this->resize(nodeName,1)==FAIL){
        cout<<"unable to realloc from add entry mode 1 on node: "<< nodeName<<endl;
        return FAIL;
      }
    }
  }
  else if(nodeName < 0 ) return FAIL;
  if(this->offsets[nodeName]!=INVALID) return FAIL;
  this->offsets[nodeName] = entryOffset;
  if(nodeName > this->numberOfEntries){
    this->numberOfEntries=nodeName+1;
  }
  return OK;
}
int index::getEntry(int entryNumber){
  if (entryNumber > (this->numberOfEntries - 1) || entryNumber < 0) {
    cout<<"out of bounds"<<endl;
    return FAIL;
  }
  if(this->offsets[entryNumber] == INVALID){
    std::cout << "empty" << std::endl;
    return FAIL;
  }
  return this->offsets[entryNumber];
}
OK_SUCCESS index::resize(int newsize,int mode){
  if(newsize < this->sizeOfIndex) return FAIL;
  switch (mode) {
    case 1:
      this->offsets = (int*) realloc(this->offsets,2*this->sizeOfIndex);
      this->sizeOfIndex = 2*this->sizeOfIndex;
      return OK;
    case 2:
      this->offsets = (int*) realloc(this->offsets,newsize + 10);
      this->sizeOfIndex = newsize;
      return OK;
    case 3:
      this->offsets = (int*) realloc(this->offsets,newsize*this->sizeOfIndex);
      this->sizeOfIndex = newsize*this->sizeOfIndex;
      return OK;
    default: return FAIL;
  }
}
