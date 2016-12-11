//
// Created by Marcus on 11/12/2016.
//
#include <iostream>
#include <cstdlib>

#include "grail.h"
#include "stack.h"
#include "defines.h"

void assignComponent(component* compArray, int &arraySize, int position, component* elem) {
   if (position >= arraySize) {
      arraySize *= 2;
      compArray = (component*) realloc(compArray, arraySize);
   }
   compArray[position] = *elem;
}

OK_SUCCESS grail::calculateSCC(n_index *subGraphIndex, buffer *subGraphBuffer) {
   int lowestIndex;
   tarjanNode* nodes;
   int numberOfGraphNodes = subGraphIndex->getNumberOfEntries();
   int numberOfComponents = 0;
   int compArraySize = COMPONENTS_ESTIMATE;
   component* components = (component*) malloc(COMPONENTS_ESTIMATE*sizeof(component));
   int* idBelongsToComponent = (int*) malloc(numberOfGraphNodes*sizeof(int));
   for (int i=0; i<numberOfGraphNodes; i++) {
      idBelongsToComponent[i] = INVALID;
   }
   
   lowestIndex = 0;
   nodes = (tarjanNode*) malloc(subGraphIndex->getNumberOfEntries() * sizeof(tarjanNode));
   for (int i=0; i<subGraphIndex->getNumberOfEntries(); i++) {
      nodes[i].nodeName = i;
      nodes[i].tIndex = INVALID;
      nodes[i].lowlink = INVALID;
      nodes[i].DFSInitialized = false;
      nodes[i].onTarjanStack = false;
   }
   stack* DFSStack = new stack(STACK_SIZE);
   stack* TarjanStack = new stack(STACK_SIZE);
   
   for (int i=0; i<numberOfGraphNodes; i++) {
      while (idBelongsToComponent[i] == INVALID) {
         int numberOfNeighbors;
         uint32_t* neighbors;
         tarjanNode* v = nodes+i;
         //DFSStack->push(v.nodeName);
         //v.DFSInitialized = true;
         do{
            // Set the depth index for v to the smallest unused index
            if (v->tIndex == INVALID) {
               v->tIndex = lowestIndex;
               v->lowlink = lowestIndex;
               lowestIndex++;
               TarjanStack->push(v->nodeName);
               v->onTarjanStack = true;
            }
            
            // Consider successors of v
            int offset = subGraphIndex->getEntry(v->nodeName);
            if (offset != INVALID) {
               neighbors = subGraphBuffer->getNeighbors(numberOfNeighbors, offset);
               int j;
               for (j=0; j<numberOfNeighbors; j++) {
                  if (!nodes[neighbors[j]].DFSInitialized) {
                     DFSStack->push(v->nodeName);
                     v->DFSInitialized = true;
                     v = &nodes[neighbors[j]];
                     break;
                  }
                  else {
                     if (idBelongsToComponent[neighbors[j]] == INVALID && nodes[neighbors[j]].lowlink < v->lowlink) {
                        v->lowlink = nodes[neighbors[j]].lowlink;
                     }
                     continue;
                  }
               }
               if (j == numberOfNeighbors) {
                  v->DFSInitialized = true;
                  int tmp = DFSStack->pop();
                  if (tmp != INVALID) v = &nodes[tmp];
               }
            }
            else break;
         }while (!DFSStack->isEmpty());
         //v = &nodes[i];
         
         // If v is a root node, pop the stack and generate an SCC
         component* a = new component();
         a->setCompId(numberOfComponents);
         int* commponentNodes = new int[TarjanStack->getNumberOfElements()];
         int c = 0;
         tarjanNode* w;
         do {
            w = nodes+ TarjanStack->pop();
            w->onTarjanStack = false;
            commponentNodes[c] = w->nodeName;
            idBelongsToComponent[w->nodeName] = numberOfComponents;
         } while (w->tIndex != w->lowlink);
         a->setNodesContained(commponentNodes);
         a->setNumberOfNodes(c);
         assignComponent(components, compArraySize, numberOfComponents, a);
         //insert a into current SCC
         numberOfComponents++;
      }
   }
   this->SCC = new stronglyConnectedComponents(components, numberOfComponents, idBelongsToComponent);
   return OK;
}
