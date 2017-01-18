#ifndef DEFINES_H
#define DEFINES_H
#include <stdint.h>
// #include <memory.h>
#include <stdlib.h>

#define YES -9
#define MAYBE -8
#define NO -7

#define NOT_IN_UPDATE_INDEX -6
#define ALREADY_IN_UPDATE_INDEX -5

#define FULL -4
#define INVALID -3
#define FAIL -2
#define OK -1

#define FROM 0
#define TO 1
#define RECALCULATE_CONECTED_COMPONENTS 0.6

#define MIN_RANK 0
#define RANK 1

#define LIST_NODE_SIZE 5
#define BUFFER_SIZE 10
#define INDEX_SIZE 6
#define UPDATE_INDEX_SIZE 200
#define STACK_SIZE 15
#define RANK_SIZE 1
#define COMPONENTS_ESTIMATE 15
#define BFS_FRINGE_SIZE 50
#define HASH_SIZE 1000
#define HASH_PERCISION 2
#define THREAD_NUMBER 4 //Most PCs have 4-core processors

using namespace std;
typedef int ptr;
typedef int OK_SUCCESS;

#endif