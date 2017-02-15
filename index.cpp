#include <iostream>
#include "index.h"

n_index::n_index(int size){
  this->sizeOfIndex = size;
  this->offsets =(int*)  malloc(this->sizeOfIndex*sizeof(int));
  this->CCnum =(int*)  malloc(this->sizeOfIndex*sizeof(int));
  this->numberOfEntries = 0;
  for (int i = 0; i < size; i++) {
    this->offsets[i]= INVALID;
    this->CCnum[i] = INVALID;
  }
    this->totalConnectedComponents = 0;
}
n_index::~n_index(){
  free(this->offsets);
  this->sizeOfIndex = INVALID;
  this->numberOfEntries =0;
}
OK_SUCCESS n_index::setNumberOfEntries(int numberOfEntries){
  this->numberOfEntries = numberOfEntries;
  return OK;
}
int n_index::getNumberOfEntries(){
  return this->numberOfEntries;
}
OK_SUCCESS n_index::setSizeOfIndex(int sizeOfIndex){
  this->sizeOfIndex = sizeOfIndex;
  return OK;
}
int n_index::getSizeOfIndex(){
  return this->sizeOfIndex;
}
OK_SUCCESS n_index::addEntry(int entryOffset , int nodeName){
  if(nodeName >= this->sizeOfIndex) {
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
  if(nodeName >= this->numberOfEntries){
    this->numberOfEntries=nodeName+1;
  }
  return OK;
}
int n_index::getEntry(int entryNumber){
  if(entryNumber<0) return FAIL;
  if (entryNumber >= (this->sizeOfIndex)) {
    this->resize(entryNumber,2);
  }
  if(this->offsets[entryNumber] == INVALID){

    return INVALID;
  }
  return this->offsets[entryNumber];
}
OK_SUCCESS n_index::resize(int newsize,int mode){
  if(newsize < this->sizeOfIndex  && mode==2) return FAIL;
  int oldsize = this->sizeOfIndex;
  switch (mode) {
    case 1:
      this->offsets = (int*) realloc(this->offsets,2*this->sizeOfIndex*sizeof(int));
      this->CCnum = (int*) realloc(this->CCnum,2*this->sizeOfIndex*sizeof(int));
      this->sizeOfIndex = 2*this->sizeOfIndex;
      for(int i = oldsize ; i < this->sizeOfIndex; ++i) {
            this->offsets[i]= INVALID;
            this->CCnum[i]= INVALID;
      }
      return OK;
    case 2:
      this->offsets = (int*) realloc(this->offsets,(newsize + 10)*sizeof(int));
      this->CCnum = (int*) realloc(this->CCnum,(newsize + 10)*sizeof(int));
      this->sizeOfIndex = newsize + 10;
      for(int i = oldsize; i < this->sizeOfIndex; ++i) {
            this->offsets[i]= INVALID;
            this->CCnum[i]= INVALID;
      }
      return OK;
    case 3:
      this->offsets = (int*) realloc(this->offsets,newsize*this->sizeOfIndex*sizeof(int));
      this->CCnum = (int*) realloc(this->CCnum,newsize*this->sizeOfIndex*sizeof(int));
      this->sizeOfIndex = newsize*this->sizeOfIndex;
      for(int i = oldsize ; i < this->sizeOfIndex; ++i) {
            this->offsets[i]= INVALID;
            this->CCnum[i]= INVALID;
      }
      return OK;
    default: return FAIL;
  }
}

int n_index::getCCnum(int nodeName)
{
  if(nodeName < 0 || nodeName >= this->sizeOfIndex) return FAIL;
  return this->CCnum[nodeName];
}

OK_SUCCESS n_index::setCCnum(uint32_t nodeName, int CCname)
{
  if (CCname < 0 || CCname >= this->sizeOfIndex) return FAIL;
  this->CCnum[nodeName] = CCname;
  return OK;
}

void n_index::printCCnum(){
    cout<<"Printing CCnums"<<endl;
    for (int i=0; i<this->sizeOfIndex; i++){
        cout<<"--Entry: "<<i<< "--Offset: "<<this->offsets[i]<<"--CCnum: "<<this->CCnum[i]<<endl;
    }
}

int n_index::getTotalConnectedComponents() const {
    return totalConnectedComponents;
}

void n_index::setTotalConnectedComponents(int totalConnectedComponents) {
    n_index::totalConnectedComponents = totalConnectedComponents;
}

void n_index::printGraph(buffer* buff) {
    int numberOfNeighbors;
    uint32_t *neighbors;
    for (int i = 0; i < sizeOfIndex; i++) {
        cout<<i<<" -> ";
        neighbors = buff->getNeighbors(numberOfNeighbors, getEntry(i));
        if(neighbors != NULL){
            for (int j = 0; j < numberOfNeighbors; j++) {
                cout<<neighbors[j]<<", ";
            }
        }

        cout<<endl;
    }
}
