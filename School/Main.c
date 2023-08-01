#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "Classes.h"

#define MAX_LEVEL 12
#define MIN_LEVEL 1

#define MAX_CLAAS 10
#define MIN_CLASS 1

#define MAX_GRADE 100
#define MIN_GRADE 0

#define NUM_OF_LEVELES 12
#define NUM_OF_ClASSES 10

enum menu_inputs {
    Insert = '0',
    Delete = '1',
    Edit = '2',
    Search = '3',
    Showall = '4',
    Top10 = '5',
    UnderperformedStudents = '6',
    Average = '7',
    Export = '8',
    Exit = '9'
};

char* readPhone()
{
    char phone[11];

    printf("Enter your phone number\n");
    scanf("%s", &phone);

    return phone;
}
Student* readStudent()
{
    char firstName[25];
    char lastName[25];
    char phone[11];

    printf("Enter your first name\n");
    scanf("%s", &firstName);

    printf("Enter your last name\n");
    scanf("%s", &lastName);

    strcpy(phone, readPhone());


    Student* s = createStudent(firstName, lastName, phone);
    return s;
}

void readGrads(Student* s)
{
    int grades[10];
    for (int i = 0; i < 10; i++)
    {
        printf("enter your grade %d\n", i);
        scanf("%d", &grades[i]);
        while (grades[i] < MIN_GRADE || grades[i] > MAX_GRADE)
        {
            printf("Invalid grade! enter your grade %d again\n", i);
            scanf("%d", &grades[i]);
        }

    }
    fillGrades(s, grades);
}

Student* search(char* phone, Student* school[NUM_OF_LEVELES][NUM_OF_ClASSES])
{
    Student* s;
    for (int level = 0; level < NUM_OF_LEVELES; level++) {
        for (int cls = 0; cls < NUM_OF_ClASSES; cls++)
        {
            s = searchStudent(school[level][cls], phone);
            if (s != NULL)
            {
                return s;
            }
        }

    }
    return NULL;
}

void menu(Classes* school[NUM_OF_LEVELES][NUM_OF_ClASSES]) {
    Student* s;
    char input;
    char firstName[25];
    char lastName[25];
    char phone[11];
    int level;
    int cls;
    int grades[10];
    // school.name = "schoolName";
    do {
        //printf("\n|School Manager<::>Home|\n");
        //printf("--------------------------------------------------------------------------------\n");
        //printf("Welcome to ( %s ) School!\nYou have inserted ( %zu ) students.\n\n", school.name, school.numOfStudents);
        printf("\t[0] |--> Insert\n");
        printf("\t[1] |--> Delete\n");
        printf("\t[2] |--> Edit\n");
        printf("\t[3] |--> Search\n");
        printf("\t[4] |--> Show All\n");
        printf("\t[5] |--> Top 10 students per course\n");
        printf("\t[6] |--> Underperformed students\n");
        printf("\t[7] |--> Average per course\n");
        printf("\t[8] |--> Export\n");
        printf("\t[9] |--> Exit\n");
        printf("\n\tPlease Enter Your Choice (0-9): ");
        input = getc(stdin);
        fflush(stdin);
        getc(stdin);
        switch (input) {
        case Insert:
            s = readStudent();
            printf("Enter your level\n");
            scanf("%d", &level);

            while (level < MIN_LEVEL || level > MAX_LEVEL)
            {
                printf("Level does not exist, try again");
                scanf("%d", &level);
            }

            level--;

            printf("Enter your class\n");
            scanf("%d", &cls);

            while (cls < MIN_CLASS || cls > MAX_CLAAS)
            {
                printf("class does not exist, try again");
                scanf("%d", &cls);
            }

            cls--;
            
            readGrads(s);

            school[level][cls] = addNode(school[level][cls], s);
            //insertNewStudent();
            break;
        case Delete:
            //deleteStudent();
            break;
        case Edit:
            //editStudentGrade();
            break;
        case Search:
            strcpy(phone, readPhone());
            s = search(phone, school);
            if (s != NULL)
            {
                printf("%s ", phone);
                printName(s);
            }
            else
            {
                printf("Student does not exist\n");
            }
            break;
        case Showall:
            //printAllStudents();
            break;
        case Top10:
            //printTopNStudentsPerCourse();
            break;
        case UnderperformedStudents:
            //printUnderperformedStudents();
            break;
        case Average:
            //printAverage();
            break;
        case Export:
            //exportDatabase();
            break;
        case Exit:
            //handleClosing();
            break;
        default:
            printf("\nThere is no item with symbol \"%c\".Please enter a number between 1-10!\nPress any key to continue...",
                input);
            getc(stdin);
            getc(stdin);
            break;
        }
    } while (input != Exit);
}

int main()
{
    Classes* school[NUM_OF_LEVELES][NUM_OF_ClASSES];

    for (int level = 0; level < NUM_OF_LEVELES; level++) {
        for (int cls = 0; cls < NUM_OF_ClASSES; cls++)
        {
            school[level][cls] = createClasses();
        }

    }

    FILE* file = fopen("../students_with_class.txt", "r");
    if (file == NULL) {
        perror("Error opening the file");
        return 1;
    }

    else
    {
        char line[256];
        while (fgets(line, sizeof(line), file) != NULL) {
            char* items[15];

            char* s = " ";

            items[0] = strtok(line, s);
            for (int i = 1; i < 15; i++) {
                items[i] = strtok(NULL, s);
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
    menu(school);

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



