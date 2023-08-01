#include "Student.h"

Student* createStudent(const char* firstName, const char* lastName, const char* phone) {
    Student* newStudent = (Student*)malloc(sizeof(Student));
    if (newStudent != NULL) {
        strcpy(newStudent->phone, phone);
        newStudent->firstName = (char*)malloc(strlen(firstName) + 1);
        newStudent->lastName = (char*)malloc(strlen(lastName) + 1);
        if (newStudent->firstName != NULL && newStudent->lastName != NULL) {
            strcpy(newStudent->firstName, firstName);
            strcpy(newStudent->lastName, lastName);

        }
        else {
            free(newStudent->firstName);
            free(newStudent->lastName);
            free(newStudent);
            return NULL;
        }
    }
    return newStudent;
}

void printName(Student* s)
{
    printf("%s %s\n", s->firstName, s->lastName);
}

void fillGrades(Student* student, const int* grades) {
    for (int i = 0; i < NUM_OF_GRADES; i++) {
        student->grades[i] = grades[i];
    }
}

void freeStudent(Student* student) {
    if (student != NULL) {
        free(student->firstName);
        free(student->lastName);
    }
    free(student);
}