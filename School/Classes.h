#pragma once
#include "Node.h"

typedef struct {
    Node* head;
}Classes;

Classes* createClasses(Student* student);

Classes* addNode(Classes* classes, Student* student);

void freeClasses(Classes* classes);