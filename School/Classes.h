#pragma once
#include "Node.h"

typedef struct {
    Node* head;
}Classes;

Classes* createClasses();

Classes* addNode(Classes* classes, Student* student);

void print(Classes* classes);

void freeClasses(Classes* classes);
