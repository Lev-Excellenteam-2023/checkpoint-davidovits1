#include "Node.h"

Node* creatNode(const Student* student)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode != NULL) {
        newNode->student = student;
        newNode->next = NULL;
    }
	return newNode;
}

void freeNode(Node* node) {
    if (node != NULL) {
		freeStudent(node->student);
        free(node);
    }
}