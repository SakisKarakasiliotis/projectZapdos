#include <iostream>
#include <string.h>
#include <stdio.h>
#include "my_hash.h"

//-------------HASH CLASS-------------
hashClass::hashClass(int initialSize, short int precision)
{
   this->table = new bucket[initialSize];
   this->precision = precision;
}

hashClass::~hashClass()
{
   delete this->table;
}

uint32_t hashClass::hashFun(const char* input)
{
   return (*(uint32_t*) input)>> precision;
}

bool hashClass::check_hash(const char* input)
{
   uint32_t bucket = hashFun(input);
   if (this->table[bucket].existsInBucket(input))
      return true;
   return false;
}

//-------------BUCKET CLASS-------------
bucket::bucket()
{
   this->tableSize = 2;
   this->bucketTable = (char**) malloc(tableSize*sizeof(char*));
   this->numOfElements = 0;
}

bucket::~bucket()
{
   free(this->bucketTable);
}

void bucket::insert(const char* input)
{
   if (this->numOfElements == this->tableSize)
   {
      this->tableSize *= 2;
      this->bucketTable = (char**) realloc(bucketTable, this->tableSize*sizeof(char*)); 
   }
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