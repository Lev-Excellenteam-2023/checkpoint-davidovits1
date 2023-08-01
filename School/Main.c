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
    scanf("%24s", &firstName);

    printf("Enter your last name\n");
    scanf("%25s", &lastName);

    strcpy(phone, readPhone());


    Student* s = createStudent(firstName, lastName, phone);
    return s;
}

int readLevel()
{
    int level;
    printf("Enter your level\n");
    scanf("%d", &level);

    while (level < MIN_LEVEL || level > MAX_LEVEL)
    {
        printf("Level does not exist, try again\n");
        scanf("%d", &level);
    }
    return level;
}

int readClass()
{
    int cls;
    printf("Enter your level\n");
    scanf("%d", &cls);

    while (cls < MIN_CLASS || cls > MAX_CLAAS)
    {
        printf("Level does not exist, try again\n");
        scanf("%d", &cls);
    }
    return cls;
}

void printAllStudents(Classes* school[NUM_OF_LEVELES][NUM_OF_ClASSES])
{
    for (int level = 0; level < NUM_OF_LEVELES; level++) {
        for (int cls = 0; cls < NUM_OF_ClASSES; cls++)
        {
            if (school[level][cls]->head != NULL)
            {
                printf("\n\n\n\n\nlevel:%d class:%d\n\n\n\n\n", level, cls);
                print(school[level][cls]);
            }

        }
    }
}

int readIndexCourse()
{
    int indexCourse;
    printf("enter index of course\n");
    scanf("%d", &indexCourse);

    while (indexCourse < 0 || indexCourse > 9)
    {
        printf("Course does not exist, enter index of course\n");
        scanf("%d", &indexCourse);
    }
    return indexCourse;
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

bool deleteStudentByPhone(Classes* school[NUM_OF_LEVELES][NUM_OF_ClASSES], char* phone)
{
    bool deleted = false;
    for (int level = 0; level < NUM_OF_LEVELES; level++) {
        for (int cls = 0; cls < NUM_OF_ClASSES; cls++)
        {
            deleted = deleatStudent(school[level][cls], phone);
            if (deleted)
            {
                return deleted;
            }

        }

    }

    return deleted;

}

void edit(Classes* school[NUM_OF_LEVELES][NUM_OF_ClASSES])
{
    int index, grade;
    char phone[11];
    Student* s;

    strcpy(phone, readPhone());

    s = search(phone, school);
    if (s == NULL)
    {
        printf("Student does not exist\n");
        return;
    }
    printStudent(s);

    printf("enter index of grade\n");
    scanf("%d", &index);
    while (index < 0 || index > 9)
    {
        printf("Invalid index! enter index again\n");
        scanf("%d", &index);
    }
    printf("enter grade to change\n");
    scanf("%d", &grade);

    while (grade < MIN_GRADE || grade > MAX_GRADE)
    {
        printf("Invalid grade! enter grade again\n");
        scanf("%d", &grade);
    }

    editStudent(s, index, grade);
    printStudent(s);
}

void printAverage(Classes* school[NUM_OF_LEVELES][NUM_OF_ClASSES], int indexCourse)
{
    for (int level = 0; level < NUM_OF_LEVELES; level++) {

        double avg = 0.0;
        for (int cls = 0; cls < NUM_OF_ClASSES; cls++)
        {
            avg += averageClasses(school[level][cls], indexCourse);
        }
        avg = avg / NUM_OF_ClASSES;
        printf("average course %d level %d : %f\n", indexCourse, level, avg);
    }
}

void menu(Classes* school[NUM_OF_LEVELES][NUM_OF_ClASSES]) 
{
    Student* s;
    char input;
    char firstName[25];
    char lastName[25];
    char phone[11];
    int level, cls, grade, indexCourse;
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

            level = readLevel();
            level--;

            cls = readClass();
            cls--;
     
            readGrads(s);

            school[level][cls] = addNode(school[level][cls], s);
            break;

        case Delete:
            strcpy(phone, readPhone());
            bool deleted = deleteStudentByPhone(school, phone);

            if (deleted)
                printf("deleted\n");
            else
                printf("student not found\n");

            break;

        case Edit:
            edit(school);

            break;

        case Search:
            strcpy(phone, readPhone());
            s = search(phone, school);
            if (s != NULL)
            {
                printf("%s ", phone);
                printStudent(s);
            }
            else
                printf("Student does not exist\n");
          
            break;

        case Showall:
            printAllStudents(school);
            break;

        case Top10:
            //printTopNStudentsPerCourse();
            break;

        case UnderperformedStudents:
            //printUnderperformedStudents();
            break;

        case Average:
            indexCourse = readIndexCourse();
            printAverage(school, indexCourse);
            break;

        case Export:
            //exportDatabase();
            break;
        case Exit:
            for (int level = 0; level < NUM_OF_LEVELES; level++) {
                for (int cls = 0; cls < NUM_OF_ClASSES; cls++)
                {
                    freeClasses(school[level][cls]);
                }
            }
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


    return 0;
}



