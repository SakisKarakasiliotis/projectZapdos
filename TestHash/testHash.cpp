#include <iostream>
#include <cstdlib>
#include <memory.h>
#include "myHash.h"

#define INITIAL_SIZE 10
#define PERCISION 2

// Remember to use std::cout

void genRandom(char*, const int);

int main(int argc, char* argv[]) {
   srand(time(NULL));
   int strSize;
   int actualPositives = 0;
   int uniqueStrings = 0;
   char* myString;
   hashClass* HashedStrings = new hashClass(INITIAL_SIZE, PERCISION);

   do {
      strSize = rand()%12 + 3;
      myString = (char*) malloc((strSize+1)*sizeof(char)); //1 extra char for the NULL termination character
      genRandom(myString, strSize);
      std::cout << endl << "We will hash-check \"" << myString << "\", ";
      std::cout << "which is " << strSize << " chars long." << endl;
      if (HashedStrings->checkHash(myString)) {
         actualPositives++;
         std::cout << endl << "\"" << myString << "\" exists in the list!" << endl;
         std::cout << "Strings encountered more than once: " << actualPositives << endl;
      }
      else {
         uniqueStrings++;
         std::cout << endl << "\"" << myString << "\" has been added to the list!" << endl;
         std::cout << "Unique strings checked so far: " << uniqueStrings << endl;
      }
      free(myString);
   } while (actualPositives < 10);

   delete HashedStrings;
   return 0;
}

//random string generator source:
//http://stackoverflow.com/questions/440133/how-do-i-create-a-random-alpha-numeric-string-in-c
void genRandom(char *s, const int len) {
    static const char alphanum[] =
        "0123456789 "
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ\t"
        "abcdefghijklmnopqrstuvwxyz\n";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
//Those beautiful bastards at stackoverflow even took into 
//consideration the last character to be NULL :')
    s[len] = 0;
}