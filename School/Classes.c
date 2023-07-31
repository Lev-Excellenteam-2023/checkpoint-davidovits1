#include "Classes.h"

Classes* createClasses()
{
	Classes* newClasses = (Classes*)malloc(sizeof(Classes));
	newClasses->head = NULL;
	return newClasses;
}

Classes* addNode(Classes* classes, Student* student)
{
	//first element
	if (classes->head == NULL)
	{
		classes->head = creatNode(student);
		return classes;
	}

	else
	{
		Node* newHead = creatNode(student);
		newHead->next = classes->head;
		classes->head = newHead;
		return classes;
	}

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