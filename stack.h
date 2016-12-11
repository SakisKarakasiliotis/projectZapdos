//
// Created by Windows 8 on 10-Dec-16.
//

#ifndef PROJECTZAPDOS_STACK_H
#define PROJECTZAPDOS_STACK_H


class stack {
private:
    int *stck;
    int size;
    int position;
public:
    stack(int size);
    ~stack();

    bool push(int elem);
    int pop();
    int softPop();
    int getSize();
    bool isEmpty();
    bool isFull();
    bool resize();
    bool contains(int nodeName);
   int getNumberOfElements();
};


#endif //PROJECTZAPDOS_STACK_H
