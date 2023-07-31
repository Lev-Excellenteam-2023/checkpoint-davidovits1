#pragma once
#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH 50

// Function to read data from the file into int and char array
int readFromFile(const char* filename, int* age, char* firstName, char* lastName) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening the file");
        return 1; // Return 0 to indicate failure
    }

    // Read the integer value (age) from the file
    if (fscanf(file, "%d", age) != 1) {
        printf("Failed to read the age from the file.\n");
        fclose(file);
        return 1;
    }

    // Read the first and last name from the file
    if (fscanf(file, "%s %s", firstName, lastName) != 2) {
        printf("Failed to read the first and last name from the file.\n");
        fclose(file);
        return 1;
    }

    fclose(file);
    return 0; // Return 1 to indicate success
}