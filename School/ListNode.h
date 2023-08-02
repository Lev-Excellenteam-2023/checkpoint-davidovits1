#pragma once
#include "Node.h"

typedef struct {
    Node* head;
}ListNode;

ListNode* createListNode();

ListNode* addNode(ListNode* classes, Student* student);

Student* searchStudent(ListNode* cls, char* phone);

void print(ListNode* classes);

void freeListNode(ListNode* classes);

bool deleatStudent(ListNode* cls, char* phone);

double averageClasses(ListNode* cls, int indexCourse);

void topTenPerClass(ListNode* cls, Student** topTenStudents);