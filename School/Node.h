#pragma once
#include "Student.h"
typedef struct  {
	Student* student;
	Node* next;
}Node;

struct Node* creatNode(const Student* student);

void freeNode(Node* node);