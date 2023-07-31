#include "Classes.h"

Classes* createClasses(Student* student)
{
	Classes* newClasses = (Classes*)malloc(sizeof(Classes));
	newClasses->head = student;
	return newClasses;
}

Classes* addNode(Classes* classes, Student* student)
{
	Node* newHead = creatNode(student);
	newHead->next = classes->head;
	classes->head = newHead;
	return classes;
}

void freeClasses(Classes* classes)
{
	Node* temp = classes->head;
	while (temp->next != NULL)
	{
		temp = temp->next;
		freeNode(classes->head);
		classes->head = temp;
	}
	freeNode(classes->head);
}