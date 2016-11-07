#ifndef HASH_H
#define HASH_H

#include "defines.h"

class hash
{
   private:

      char** table;
      short int precision;
      uint32_t hashFun(char*);
   public:
      hash(int, int);
      ~hash();
      bool check_hash(char*);
};

#endif