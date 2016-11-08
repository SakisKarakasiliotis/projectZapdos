#include <iostream>
#include <string.h>
#include <stdio.h>
#include "my_hash.h"

hashClass::hashClass(int initialSize, short int precision)
{
   this->table = (char**) malloc(initialSize*sizeof(char*));
   for (int i=0; i<initialSize; i++)
      sprintf(this->table[i], "AA"); //We know that the input will be like "A <num> <num>"
   this->precision = precision;
}

hashClass::~hashClass()
{
   delete this->table;
}

uint32_t hashClass::hashFun(char* input)
{
   return (*(uint32_t*) input)>> precision;
}

bool hashClass::check_hash(char* input)
{
   uint32_t bucket = hashFun(input);
   if (!strcmp(this->table[bucket], input))
      return true;
   sprintf(this->table[bucket], "%s", input);
   return false;
}