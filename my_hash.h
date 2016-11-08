#ifndef MY_HASH_H
#define MY_HASH_H

#include "defines.h"

class hashClass
{
   private:

      char** table;
      short int precision;
      uint32_t hashFun(char*);
   public:
      hashClass(int, short int);
      ~hashClass();
      bool check_hash(char*);
};

#endif