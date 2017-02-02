//
// Created by Windows 8 on 10-Dec-16.
//
#include <iostream>
#include "component.h"
#include "defines.h"

component::component() {
    this->compId = INVALID;
}

component::~component() {

}

int component::getCompId() const {
    return compId;
}

void component::setCompId(int compId) {
    component::compId = compId;
}

int component::getNumberOfNodes() const {
    return numberOfNodes;
}

void component::setNumberOfNodes(int numberOfNodes) {
    component::numberOfNodes = numberOfNodes;
}

int *component::getNodesContained() const {
    return nodesContained;
}

void component::setNodesContained(int *nodesContained) {
    component::nodesContained = nodesContained;
}

int component::getNode(int node) {
    if(node<0 || node>=this->numberOfNodes){
        cout<<"Requested node "<<node<<" is out of bounds on getNode"<<endl;
        return FAIL;
    }
    return nodesContained[node];
}
