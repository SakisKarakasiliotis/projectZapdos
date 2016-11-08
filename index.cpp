#include <iostream>
#include "index.h"

n_index::n_index(int size){
  this->sizeOfIndex = size;
  this->offsets =(int*)  malloc(this->sizeOfIndex*sizeof(int));
  this->numberOfEntries = 0;
  for (int i = 0; i < size; i++) {
    this->offsets[i]= INVALID;
  }
}
n_index::~n_index(){
  free(this->offsets);
  this->sizeOfIndex = INVALID;
  this->numberOfEntries =0;
  cout << "deleting index"<<endl;
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
OK_SUCCESS n_index::addEntry(int entryOffset , int nodeName){//10 11
  if(nodeName > this->sizeOfIndex) {
       if(nodeName>2*this->sizeOfIndex){
          //  cout<<"should not be here"<<nodeName<<endl;

            if(this->resize(nodeName,2)== FAIL){
              cout<<"unable to realloc from add entry mode 2 on node: "<< nodeName<<endl;
              return FAIL;
            }
       }
       else {
            //cout<<"should be here"<<nodeName<<endl;
            if(this->resize(nodeName,1)==FAIL){
              cout<<"unable to realloc from add entry mode 1 on node: "<< nodeName<<endl;
              return FAIL;
            }
       }
  }
  else if(nodeName < 0 ) return FAIL;
  std::cout << "before invalid" << std::endl;
  if(this->offsets[nodeName]!=INVALID) return FAIL; //TODO fix this check cause garbage
  std::cout << "after invalid" << std::endl;

  this->offsets[nodeName] = entryOffset;
  if(nodeName >= this->numberOfEntries){
    cout<<"increasing number"<<endl;
    this->numberOfEntries=nodeName+1;
  }
  return OK;
}
int n_index::getEntry(int entryNumber){
  if(entryNumber<0) return FAIL;
  if (entryNumber > (this->numberOfEntries)) {
    cout<<this->numberOfEntries<<" c"<<endl;
    cout<<entryNumber<<" entry number requested is out of bounds"<<endl;
    this->resize(entryNumber,2);    
  }
  if(this->offsets[entryNumber] == INVALID){
    std::cout << "empty" << std::endl;
    return INVALID;
  }
  return this->offsets[entryNumber];
}
OK_SUCCESS n_index::resize(int newsize,int mode){
  if(newsize < this->sizeOfIndex  && mode==2) return FAIL;
  int oldsize = this->sizeOfIndex;
  //std::cout << "sizeOfIndex start " << this->sizeOfIndex <<std::endl;
  switch (mode) {
    case 1:
      this->offsets = (int*) realloc(this->offsets,2*this->sizeOfIndex*sizeof(int));
      this->sizeOfIndex = 2*this->sizeOfIndex;
      for(int i = oldsize - 1; i < this->sizeOfIndex; ++i) {
            this->offsets[i]= INVALID;
      }
      return OK;
    case 2:
      this->offsets = (int*) realloc(this->offsets,(newsize + 10)*sizeof(int));
      this->sizeOfIndex = newsize + 10;
      for(int i = oldsize - 1; i < this->sizeOfIndex; ++i) {
            this->offsets[i]= INVALID;
      }
      return OK;
    case 3:
      this->offsets = (int*) realloc(this->offsets,newsize*this->sizeOfIndex*sizeof(int));
      this->sizeOfIndex = newsize*this->sizeOfIndex;
      for(int i = oldsize - 1; i < this->sizeOfIndex; ++i) {
            this->offsets[i]= INVALID;
      }
      return OK;
    default: return FAIL;
  }
}
