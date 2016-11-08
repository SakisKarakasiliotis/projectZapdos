#ifndef MY_HASH_H
#define MY_HASH_H

#include "defines.h"

class bucket 
{
   private:
      char** bucketTable;
      int tableSize;
      int numOfElements;
      void insert(const char*);
   public:
      bucket();
      ~bucket();
      bool existsInBucket(const char*);
};

class hashClass
{
   private:
      bucket* table;
      short int precision;
      uint32_t hashFun(const char*);
   public:
      hashClass(int, short int);
      ~hashClass();
      bool check_hash(const char*);
};

#endif