#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NUM_OF_GRADES 10
#define LEN_PHONE 11

typedef struct {
    char* firstName;
    char* lastName;
    char phone[LEN_PHONE];
    int grades[NUM_OF_GRADES];
}Student;

// Function to create a new student
Student* createStudent(const char* firstName, const char* lastName, const char* phone);

// Function to fill grades in the student
void fillGrades(Student* student, const int* grades);

// Function to free the memory allocated for the student
void freeStudent(Student* student);

void printName(Student* s);

void printStudent(Student* s);

void editStudent(Student* s, int index, int grade);
