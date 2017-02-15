#include <cstdio>
#include <iostream>
#include <string.h>
#include "myHash.h"

hashClass::hashClass(int initialSize, short int precision)
{
   this->table = new bucket[initialSize];
   this->numOfBuckets = initialSize;
   this->precision = precision;
}

hashClass::~hashClass()
{
   delete[] this->table;
}

uint32_t hashClass::hashFun(const char* input)
{
   return (*(uint32_t*) input)>> precision;
}

bool hashClass::checkHash(const char* input)
{
   uint32_t bucket = hashFun(input)%this->numOfBuckets;
   if (this->table[bucket].existsInBucket(input))
      return true;
   return false;
}

bucket::bucket()
{
   this->tableSize = 2;
   this->bucketTable = (char**) malloc(tableSize*sizeof(char*));
   this->numOfElements = 0;
}

bucket::~bucket()
{
   for(int i=0; i<this->numOfElements; i++)
      free(this->bucketTable[i]);
   free(this->bucketTable);
}

void bucket::insert(const char* input)
{
   if (this->numOfElements == this->tableSize)
   {
      this->tableSize *= 2;
      this->bucketTable = (char**) realloc(bucketTable, this->tableSize*sizeof(char*));
   }
    this->bucketTable[numOfElements] = (char*) malloc ((strlen(input)+1)*sizeof(char));
   sprintf(this->bucketTable[numOfElements], "%s", input);
   this->numOfElements++;
}

bool bucket::existsInBucket(const char* input)
{
   for (int i=0; i<this->numOfElements; i++)
      if (!strcmp(bucketTable[i], input))
         return true;
   this->insert(input);
   return false;
}