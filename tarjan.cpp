//
// Created by Stupid on 11/12/2016.
//
#include <iostream>
#include <cstdlib>

#include "grail.h"
#include "stack.h"
#include "defines.h"

void assignComponent(component* compArray, int &arraySize, int position, component* elem) {
      if (position >= arraySize) {
         arraySize *= 2;
         compArray = (component*) realloc(compArray, arraySize*sizeof(component));
      }
      compArray[position] = *elem;
}

OK_SUCCESS grail::calculateSCC(n_index *subGraphIndex, n_index *subGraphIndexInv, buffer *subGraphBuffer) {
   int lowestIndex;
   tarjanNode* nodes;
   int numberOfGraphNodes = subGraphIndex->getNumberOfEntries();
    int x = subGraphIndexInv->getNumberOfEntries();
    if (x > numberOfGraphNodes) {
        numberOfGraphNodes = x;
    }
   int numberOfComponents = 0;
   int compArraySize = COMPONENTS_ESTIMATE;
   component* components = (component*) malloc(COMPONENTS_ESTIMATE*sizeof(component));
   int* idBelongsToComponent = (int*) malloc(numberOfGraphNodes*sizeof(int));
   for (int i=0; i<numberOfGraphNodes; i++) {
      idBelongsToComponent[i] = INVALID;
   }

   lowestIndex = 0;
   nodes = (tarjanNode*) malloc(numberOfGraphNodes * sizeof(tarjanNode));
   for (int i=0; i<numberOfGraphNodes; i++) {
      nodes[i] = *new tarjanNode(i);
//      nodes[i]->setNodeName(i);
//      nodes[i].tIndex = INVALID;
//      nodes[i].lowlink = INVALID;
//      nodes[i].neighborsChecked = 0;
//      nodes[i].DFSInitialized = false;
      //nodes[i].onTarjanStack = false;
   }
   stack* DFSStack = new stack(STACK_SIZE);
   stack* TarjanStack = new stack(STACK_SIZE);


   for (int i=0; i<numberOfGraphNodes; i++) {
//       std::cout << "Checking node " << i << std::endl;
       uint32_t* baseNeighbors = NULL;
       int baseNumberOfNeighbors;
       tarjanNode *currentNode = nodes + i;
      
       if (idBelongsToComponent[i] != INVALID) continue;
      
       int numberOfNeighbors;
       uint32_t *neighbors;
//     tarjanNode *currentNode = nodes + i; !!!!!!!!!!!!!!!!den allazei mesa sthn while exei logo na einai mesa?
       //DFSStack->push(currentNode.nodeName);
       //currentNode.DFSInitialized = true;

       int whileCount = 1;
       do {
           whileCount++;
           if(currentNode> nodes + x || currentNode < nodes){
               cout<<"failure is imminent"<<endl;
           }
           if(currentNode->getNodeName() == INVALID || currentNode->getNodeName() == FAIL){
               cout << "the end is coming 3" << endl;
           }
           // Set the depth index for currentNode to the smallest unused index
           if (currentNode->getTIndex() == INVALID) {
               currentNode->setTIndex(lowestIndex);
               currentNode->setLowlink(lowestIndex);
               lowestIndex++;
               TarjanStack->push(currentNode->getNodeName());
               //currentNode->onTarjanStack = true;
           }
            // Consider successors of currentNode
           int offset = subGraphIndex->getEntry(currentNode->getNodeName());
           if (offset != INVALID) {
//               if (currentNode->nodeName = i){
//                 if (baseNeighbors == NULL) {
//                     baseNeighbors = subGraphBuffer->getNeighbors(numberOfNeighbors, offset);
//                     baseNumberOfNeighbors = numberOfNeighbors;
//                 }
//                 neighbors = baseNeighbors;
//                 numberOfNeighbors = baseNumberOfNeighbors;
//             }
//             else {
//                 neighbors = subGraphBuffer->getNeighbors(numberOfNeighbors, offset);
//             }
               neighbors = subGraphBuffer->getNeighbors(numberOfNeighbors, offset);
               int j;
               for (j = 0; j < numberOfNeighbors; j++) {
                   //currentNode->neighborsChecked++;
                   if (!nodes[neighbors[j]].isDFSInitialized()) {
                       DFSStack->push(currentNode->getNodeName());
                       currentNode->setDFSInitialized(true);
                       currentNode = &nodes[neighbors[j]];
                       if(currentNode->getNodeName() == INVALID || currentNode->getNodeName() == FAIL){
                           cout << "the end is coming 2" << endl;
                       }
                       break;
                   } else {
                       if (idBelongsToComponent[neighbors[j]] == INVALID &&
                           nodes[neighbors[j]].getLowlink() < currentNode->getLowlink()) {
                           currentNode->setLowlink(nodes[neighbors[j]].getLowlink());
                       }
                       continue;
                   }
               }
               if (j == numberOfNeighbors) {
                   currentNode->setDFSInitialized(true);
                   int tmp = DFSStack->pop();
                   if (tmp != INVALID){
                       currentNode = &nodes[tmp];
                   }
                   if(currentNode> nodes + x || currentNode < nodes ){
                       cout<<"failure is imminent 2"<<endl;
                   }
                   if(currentNode->getNodeName() == INVALID || currentNode->getNodeName() == FAIL){
                       cout << "the end is coming" << endl;
                   }
               }
           } else {
               currentNode->setDFSInitialized(true);
               break;
           }
       } while (!DFSStack->isEmpty());
//       std::cout << "Exited while after loop No " << whileCount << std::endl;
       //currentNode = &nodes[i];

       // If currentNode is a root node, pop the stack and generate an SCC
       do {
           component *newComponent = new component();
           newComponent->setCompId(numberOfComponents);
           int *commponentNodes = new int[TarjanStack->getNumberOfElements()];
           int c = 0;
           tarjanNode *poppedNode;
           int nodeNo;
           do {
               nodeNo = TarjanStack->pop();
               poppedNode = nodes + nodeNo;//TODO CHECK THIS THING
               //poppedNode->onTarjanStack = false;
               commponentNodes[c] = poppedNode->getNodeName();
               c++;
               idBelongsToComponent[poppedNode->getNodeName()] = numberOfComponents;
//               std::cout << nodeNo << " was assigned to SCC " << numberOfComponents << std::endl;
           } while (poppedNode->getTIndex() != poppedNode->getLowlink());
           newComponent->setNodesContained(commponentNodes);
           newComponent->setNumberOfNodes(c);
           assignComponent(components, compArraySize, numberOfComponents, newComponent);
           //insert a into current SCC
           numberOfComponents++;
       }while (!TarjanStack->isEmpty()); // a wild do while appeared!!!!
   }

   this->SCC = new stronglyConnectedComponents(components, numberOfComponents, idBelongsToComponent);
   return OK;
}
