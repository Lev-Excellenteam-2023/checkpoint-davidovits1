#include <stdio.h>
#include "Classes.h"
#include "Levels.h"
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


	for (int level = 0; level < NUM_OF_LEVELES; level++) {
		for (int cls = 0; cls < NUM_OF_ClASSES; cls++)
		{
			 freeClasses(school[level][cls]);
		}

	}
	return 0;
}