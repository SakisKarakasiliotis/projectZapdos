#include <iostream>
#include <string.h>
#include "hash.h"

hash::hash(int initialSize, short int precision)
{
   this->table = (char*) malloc(initialSize*sizeof(char*));
   for (int i=0; i<initialSize; i++)
      sprintf(this->table[i], "AA"); //We know that the input will be like "A <num> <num>"
   this->precision = precision;
}

hash::~hash()
{
   delete this->table;
}

uint32_t hash::hashFun(char* input)
{
   return (*(uint32_t*) input)>> precision;
}

bool hash::check_hash(char* input)
{
   uint32_t bucket = hashFun(input);
   if (!strcmp(this->table[bucket], input))
      return true;
   sprintf(this->table[bucket], input);
   return false;
}