#pragma once
#include "Student.h"

typedef struct Node Node;

struct Node {
	Student* student;
	Node* next;
};

struct Node* creatNode(const Student* student);

void freeNode(Node* node);