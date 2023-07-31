#pragma once
#include "Node.h"

Node* createLinkdinList(Student* student);

Node* addNode(Student* student, Node* head);

void freeLinkdinList(Node* head);