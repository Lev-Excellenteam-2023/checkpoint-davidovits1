#pragma once
#include "Node.h"

typedef struct {
    Node* head;
}Classes;

Classes* createClasses();

Classes* addNode(Classes* classes, Student* student);

Student* searchStudent(Classes* cls, char* phone);

void print(Classes* classes);

void freeClasses(Classes* classes);

bool deleatStudent(Classes* cls, char* phone);

double averageClasses(Classes* cls, int indexCourse);
