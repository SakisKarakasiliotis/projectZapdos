//
// Created by Windows 8 on 10-Dec-16.
//

#ifndef PROJECTZAPDOS_COMPONENT_H
#define PROJECTZAPDOS_COMPONENT_H


class component {
public:
    component();

    virtual ~component();

    int getCompId() const;

    void setCompId(int compId);

    int getNumberOfNodes() const;

    void setNumberOfNodes(int numberOfNodes);

    int *getNodesContained() const;

    void setNodesContained(int *nodesContained);

    int getNode(int node);


private:
        int compId;
        int numberOfNodes;
        int* nodesContained;

};


#endif //PROJECTZAPDOS_COMPONENT_H
