#include <stdio.h>
#include "Classes.h"
#define NUM_OF_LEVELES 12
#define NUM_OF_ClASSES 10


int main()
{
	Classes* school[NUM_OF_LEVELES][NUM_OF_ClASSES];

    for (int level = 0; level < NUM_OF_LEVELES; level++) {
		for (int cls = 0; cls < NUM_OF_ClASSES; cls++)
		{
			school[level][cls] = createClasses();
		}
		
    }

	FILE* file = NULL;
	if (fopen_s(&file, "../students_with_class.txt", "r") != 0) {
		perror("Error opening the file");
		return 1;
	}

	else 
	{
		char line[256];
		while (fgets(line, sizeof(line), file) != NULL) {
			char* items[15];
			char* context = NULL; // Used for strtok_s

			char* s = " ";

			items[0] = strtok_s(line, s, &context);
			for (int i = 1; i < 15; i++) {
				items[i] = strtok_s(NULL, s, &context);
			}

			int level = atoi(items[3]) - 1;
			int cls = atoi(items[4]) - 1;

			int grade[10];
			for (size_t i = 0; i < 10; i++)
			{
				grade[i] = atoi(items[i + 5]);
			}

			Student* st = createStudent(items[0], items[1], items[2]);
			fillGrades(st, grade);
			//Classes* c = createClasses();
			school[level][cls] = addNode(school[level][cls], st);
		}

		fclose(file);

	}
	for (int level = 0; level < NUM_OF_LEVELES; level++) {
		for (int cls = 0; cls < NUM_OF_ClASSES; cls++)
		{
			if (school[level][cls]->head != NULL)
			{
				printf("level:%d class:%d\n\n\n\n\n", level, cls);
				print(school[level][cls]);
			}
			
		}

	}

	for (int level = 0; level < NUM_OF_LEVELES; level++) {
		for (int cls = 0; cls < NUM_OF_ClASSES; cls++)
		{
			 freeClasses(school[level][cls]);
		}

	}
	return 0;
}