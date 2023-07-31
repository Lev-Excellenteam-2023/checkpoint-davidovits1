#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_OF_GRADES 10

typedef struct{
    char* firstName;
    char* lastName;
    int phone;
    int grades[NUM_OF_GRADES];
}Student;

// Function to create a new student
struct Student* createStudent(const char* firstName, const char* lastName, const int phone);

// Function to fill grades in the student
void fillGrades(struct Student* student, const int* grades);

// Function to free the memory allocated for the student
void freeStudent(struct Student* student);