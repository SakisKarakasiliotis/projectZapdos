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
        std::cout << "Stack overflow!" << std::endl;
        this->resize();
    }
//    if (position == 7954) {
//        std::cout << "What's inside, yo?" << std::endl;
//    }
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
    if (stck[position] == 216756096) {
        std::cout << "The cursed one is upon us!" << std::endl;
    }
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
    size *= 2;
    stck = (int*) realloc(stck, size*sizeof(int));
    return true;
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