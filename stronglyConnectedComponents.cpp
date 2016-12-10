//
// Created by Windows 8 on 10-Dec-16.
//
#include <iostream>
#include "stronglyConnectedComponents.h"
#include "defines.h"


stronglyConnectedComponents::stronglyConnectedComponents(component *components, int componentsCount, int *belongsToComponent)
        : components(components), componentsCount(componentsCount), belongsToComponent(belongsToComponent) {

}

stronglyConnectedComponents::~stronglyConnectedComponents() {

}

component *stronglyConnectedComponents::getComponents() const {
    return components;
}

void stronglyConnectedComponents::setComponents(component *components) {
    stronglyConnectedComponents::components = components;
}

int stronglyConnectedComponents::getComponentsCount() const {
    return componentsCount;
}

void stronglyConnectedComponents::setComponentsCount(int componentsCount) {
    stronglyConnectedComponents::componentsCount = componentsCount;
}

int *stronglyConnectedComponents::getBelongsToComponent() const {
    return belongsToComponent;
}

void stronglyConnectedComponents::setBelongsToComponent(int *belongsToComponent) {
    stronglyConnectedComponents::belongsToComponent = belongsToComponent;
}

component *stronglyConnectedComponents::getComponent(int id) {
    if(id < 0 || id >= this->componentsCount){
        std::cout<<"Requested component is out of Bounds on getComponent"<<std::endl;
        return NULL;
    }
    if(this->components[id].getCompId() == INVALID || this->components[id].getCompId() < 0){
        std::cout<<"Requested component doesn't exist getComponent"<<std::endl;
        return NULL;
    }
    return components+id;
}

int stronglyConnectedComponents::checkBelongsToComponent(int id) {
    if(id < 0 ){
        std::cout<<"Requested component is out of Bounds on checkBelongsToComponent"<<std::endl;
        return FAIL;
    }
    return this->belongsToComponent[id];
}


