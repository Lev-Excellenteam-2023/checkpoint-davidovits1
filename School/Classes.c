#include "Classes.h"

Classes* createClasses()
{
	Classes* newClasses = (Classes*)malloc(sizeof(Classes));
	if (newClasses != NULL) {
		newClasses->head = NULL;
	}
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

Student* searchStudent(Classes* cls, char* phone)
{
	if (cls->head == NULL)
	{
		return NULL;
	}

	else
	{
		Node* temp = cls->head;
		while (temp != NULL && temp->next != NULL)
		{
			if (temp->student != NULL)
			{
				if (strcmp(temp->student->phone, phone) == 0)
				{
					return temp->student;
				}
			}
			if (temp->next == NULL)
			{
				printf("hii");
			}

			temp = temp->next;
		}

		return NULL;
	}
}

void print(Classes* classes)
{
	Node* temp = classes->head;
	while (temp != NULL)
	{
		printf("%s %s %s\n", temp->student->firstName, temp->student->lastName, temp->student->phone);
		temp = temp->next;
	}
}

void freeClasses(Classes* classes)
{
	Node* temp = classes->head;
	while (temp != NULL)
	{
		temp = temp->next;
		freeNode(classes->head);
		classes->head = temp;
	}
	free(classes);
}

