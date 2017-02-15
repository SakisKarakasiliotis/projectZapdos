#include <iostream>
#include <cstdlib>

#include "job.h"

int job::getID()
{
   return this->ID;
}

OK_SUCCESS job::setID(int ID)
{
   this->ID = ID;
   return OK;
}


int job :: getStartNode() {
   return this->startNode;
}

OK_SUCCESS job :: setStartNode(int node) {
  this->startNode = node;
  return OK;
}

int job :: getGoalNode() {
  return this->goalNode;
}

OK_SUCCESS job :: setGoalNode(int node) {
  this->goalNode= node;
  return OK;
}