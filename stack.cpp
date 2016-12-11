//
// Created by Windows 8 on 10-Dec-16.
//

#include "stack.h"

#include <cstdlib>
#include <iostream>

#include "defines.h"

stack::stack(int size) {
    this->size = size;
    this->position = 0;
    stck = (int*) malloc(size * sizeof(int));
}

stack::~stack() {
    free(this->stck);
}

bool stack::push(int elem) {
    if (this->isFull()) {
        std::cout << "Stack overflow!" << endl;
        this->resize();
    }
    this->stck[position] = elem;
    position++;
    return true;
}

int stack::pop() {
    if (this->isEmpty()) {
        std::cout << "Stack is empty!" << std::endl;
        return INVALID;
    }
    position--;
    return this->stck[position];
}
int stack::softPop() {
    if (this->isEmpty()) {
        std::cout << "Stack is empty!" << std::endl;
        return INVALID;
    }
    return this->stck[position];
}

int stack::getSize() {
    return this->size;
}

bool stack::isEmpty() {
    if (this->position == 0) return true;
    return false;
}

bool stack::isFull() {
    if (this->position == size) return true;
    return false;
}

bool stack::resize() {
    this->size *= 2;
    this->stck = (int*) realloc(this->stck, this->size*sizeof(int));
}

bool stack::contains(int nodeName) {
    for (int i=0; i<position; i++) {
        if (stck[i] == nodeName) {
            return true;
        }
    }
    return false;
}

int stack::getNumberOfElements(){
    return this->position;
}