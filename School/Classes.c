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
		while (temp != NULL)
		{
			if (temp->student != NULL)
			{
				if (strcmp(temp->student->phone, phone) == 0)
				{
					return temp->student;
				}
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
		printStudent(temp->student);
		temp = temp->next;
	}
}

bool deleatStudent(Classes* cls, char* phone)
{
	Node* n = cls->head;
	if (n != NULL)
	{
		if (strcmp(phone, n->student->phone) == 0)
		{
			cls->head = cls->head->next;
			freeNode(n);
			return true;
		}

		while (n->next != NULL)
		{
			if (strcmp(phone, n->next->student->phone) == 0)
			{
				Node* temp = n->next->next;
				freeNode(n->next);
				n->next = temp;
				return true;
			}
			n = n->next;
		}
	}

	return false;
}

double averageClasses(Classes* cls, int indexCourse)
{
	double avg = 0.0;
	int count = 0;
	Node* temp = cls->head;
	while (temp != NULL)
	{
		avg += temp->student->grades[indexCourse];
		temp = temp->next;
		count++;
	}
	return avg / count;
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

