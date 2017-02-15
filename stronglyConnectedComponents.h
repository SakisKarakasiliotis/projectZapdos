#ifndef PROJECTZAPDOS_STRONGLYCONNECTEDCOMPONENTS_H
#define PROJECTZAPDOS_STRONGLYCONNECTEDCOMPONENTS_H

#include "component.h"

class stronglyConnectedComponents {
public:
    ~stronglyConnectedComponents();

    stronglyConnectedComponents(component *components, int componentsCount, int *belongsToComponent);

    component *getComponents() const;

    component* getComponent(int id);

    void setComponents(component *components);

    int getComponentsCount() const;

    void setComponentsCount(int componentsCount);

    int *getBelongsToComponent() const;

    void setBelongsToComponent(int *belongsToComponent);

    int checkBelongsToComponent(int id);



private:
    component* components;
    int componentsCount; //1 based
    int* belongsToComponent;

};


#endif //PROJECTZAPDOS_STRONGLYCONNECTEDCOMPONENTS_H
