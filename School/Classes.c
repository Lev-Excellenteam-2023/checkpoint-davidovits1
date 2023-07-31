#include "Classes.h"

Node* createLinkdinList(Student* student)
{
	Node* head = creatNode(student);
	return head;
}

Node* addNode(Student* student, Node* head)
{
	Node* newHead = creatNode(student);
	newHead->next = head;
	return newHead;
}

void freeLinkdinList(Node* head)
{
	Node* temp = head;
	while (temp->next != NULL)
	{
		temp = temp->next;
		freeNode(head);
		head = temp;
	}
	freeNode(head);
}