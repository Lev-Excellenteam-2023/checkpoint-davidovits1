#include "Student.h"

Student* createStudent(const char* firstName, const char* lastName, const char* phone) {
    Student* newStudent = (Student*)malloc(sizeof(Student));
    if (newStudent != NULL) {
        strcpy_s(newStudent->phone,strlen(phone) + 1, phone);
        newStudent->firstName = (char*)malloc(strlen(firstName) + 1);
        newStudent->lastName = (char*)malloc(strlen(lastName) + 1);
        if (newStudent->firstName != NULL && newStudent->lastName != NULL) {
            strcpy_s(newStudent->firstName, strlen(firstName) + 1, firstName);
            strcpy_s(newStudent->lastName, strlen(lastName) + 1, lastName);

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

void fillGrades(Student* student, const int* grades) {
    for (int i = 0; i < NUM_OF_GRADES; i++) {
        student->grades[i] = grades[i];
    }
}

void freeStudent(Student* student) {
    if (student != NULL) {
        free(student->firstName);
        free(student->lastName);
        free(student);
    }
}