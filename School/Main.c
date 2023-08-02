#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "ListNode.h"
#include <ctype.h>



#define MAX_LEVEL 12
#define MIN_LEVEL 1

#define MAX_CLAAS 10
#define MIN_CLASS 1

#define MAX_GRADE 100
#define MIN_GRADE 0

#define NUM_OF_LEVELES 12
#define NUM_OF_ClASSES 10

#define TOP_STUDENTS 10

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

bool validName(char* name);
void topTen(ListNode* school[NUM_OF_LEVELES][NUM_OF_ClASSES]);

char* readPhone()
{
    char* phone = (char*)malloc(11);
    if (phone == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    int i = 0;
    printf("Enter your phone number\n");
    scanf("%10s", phone);
    while (phone[i] != '\0')
    {
        if (!isdigit(phone[i]))
        {
            printf("The number is not valid, enter your phone number\n");
            scanf("%10s", phone);
            i = 0;
        }
        else
        {
            i++;
        }
    }
    
    return phone;
}
Student* readStudent()
{
    char firstName[25];
    char lastName[25];
    char phone[11];
    char* tempPhone;
    int level;
    int cls;

    printf("Enter your first name\n");
    scanf("%24s", firstName);
    while (!validName(firstName))
    {
        printf("The first name is not valid, enter your first name\n");
        scanf("%24s", firstName);
    }

    printf("Enter your last name\n");
    scanf("%24s", lastName);
    while (!validName(lastName))
    {
        printf("The last name is not valid, enter your last name\n");
        scanf("%24s", lastName);
    }
    tempPhone = readPhone();
    strcpy(phone, tempPhone);
    free(tempPhone);
    tempPhone = NULL;

    level = readLevel();
    level--;

    cls = readClass();
    cls--;

    Student* s = createStudent(firstName, lastName, phone, level, cls);
    return s;
}

bool validName(char* name)
{
    int i = 0;
    while (name[i] != '\0')
    {
        if (!isalpha(name[i]))
        {
            return false;
        }
        else
        {
            i++;
        }
    }
    return true;

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
    printf("Enter your class\n");
    scanf("%d", &cls);

    while (cls < MIN_CLASS || cls > MAX_CLAAS)
    {
        printf("Class does not exist, try again\n");
        scanf("%d", &cls);
    }
    return cls;
}

void printAllStudents(ListNode* school[NUM_OF_LEVELES][NUM_OF_ClASSES])
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

    while (scanf("%d", &indexCourse) != 1 || indexCourse < 0 || indexCourse > 9)
    {
        while (getchar() != '\n');
        printf("Course does not exist, enter index of course\n");
    }
    return indexCourse;
}

int readGrade()
{
    int grade;
    printf("enter a grade\n");

    while (scanf("%d", &grade) != 1 || grade < MIN_GRADE || grade > MAX_GRADE)
    {
        while (getchar() != '\n');
        printf("Invalid grade! enter grade again\n");
    }
    return grade;
}

void readGrads(Student* s)
{
    int grades[10];
    for (int i = 0; i < 10; i++)
    {
        grades[i] = readGrade();

    }
    fillGrades(s, grades);
}

Student* search(char* phone, ListNode* school[NUM_OF_LEVELES][NUM_OF_ClASSES])
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

void topTen(ListNode* school[NUM_OF_LEVELES][NUM_OF_ClASSES])
{
    Student* topStudent[TOP_STUDENTS];
    double avgStudent;

    for (int level = 0; level < NUM_OF_LEVELES; level++) {
      
        for (int i = 0; i < TOP_STUDENTS; i++)
        {
            topStudent[i] = school[level][i]->head->student;
            avgStudent = averageStudent(school[level][i]->head->student);
        }
        qsort(topStudent, TOP_STUDENTS, sizeof(Student*), compareStudents);
        for (int cls = 0; cls < NUM_OF_ClASSES; cls++)
        {
            topTenPerClass(school[level][cls], topStudent);
        }
        printf("\ntop ten of level %d:\n\n", level + 1);
        for (int i = 0; i < TOP_STUDENTS; i++)
        {
            printf("%.2f ", topStudent[i]->_avg);
            printStudent(topStudent[i]);
        }
    }
 
}

bool deleteStudentByPhone(ListNode* school[NUM_OF_LEVELES][NUM_OF_ClASSES], char* phone)
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

void edit(ListNode* school[NUM_OF_LEVELES][NUM_OF_ClASSES])
{
    int index = -1;
    int grade = -1;
    char phone[11];
    char* tempPhone;
    Student* s;

    tempPhone = readPhone();
    strcpy(phone, tempPhone);
    free(tempPhone);
    tempPhone = NULL;

    s = search(phone, school);
    if (s == NULL)
    {
        printf("Student does not exist\n");
        return;
    }
    printStudent(s);

    index = readIndexCourse();

    grade = readGrade();

    editStudent(s, index, grade);
    printStudent(s);
}

void printAverage(ListNode* school[NUM_OF_LEVELES][NUM_OF_ClASSES], int indexCourse)
{
    for (int level = 0; level < NUM_OF_LEVELES; level++) {

        double avg = 0.0;
        for (int cls = 0; cls < NUM_OF_ClASSES; cls++)
        {
            avg += averageClasses(school[level][cls], indexCourse);
        }
        avg = avg / NUM_OF_ClASSES;
        printf("average course %d level %d : %f\n", indexCourse, level + 1, avg);
    }
}

void menu(ListNode* school[NUM_OF_LEVELES][NUM_OF_ClASSES]) 
{
    Student* s;
    char* tempPhone;
    //char input;
    int input;
    char phone[11];
    int level, cls, indexCourse;
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
 
        if (scanf("%d", &input) != 1) {
            // Invalid input, clear the input buffer
            while (getchar() != '\n');

            printf("\nInvalid input. Please enter a number between 0 and 9.\n");
            continue;
        }

        switch (input) {
        case 0:
            s = readStudent();

            level = s->_level;

            cls = s->_cls;
     
            readGrads(s);

            school[level][cls] = addNode(school[level][cls], s);
            break;

        case 1:
            tempPhone = readPhone();
            strcpy(phone, tempPhone);
            free(tempPhone);
            tempPhone = NULL;
            bool deleted = deleteStudentByPhone(school, phone);

            if (deleted)
                printf("deleted\n");
            else
                printf("student not found\n");

            break;

        case 2:
            edit(school);

            break;

        case 3:
            
            tempPhone = readPhone();
            strcpy(phone, tempPhone);
            free(tempPhone);
            tempPhone = NULL;
            s = search(phone, school);
            if (s != NULL)
            {
                printf("%s ", phone);
                printName(s);
            }
            else
                printf("Student does not exist\n");
          
            break;

        case 4:
            printAllStudents(school);
            break;

        case 5:
            topTen(school);
            //printTopNStudentsPerCourse();
            break;

        case 6:
            //printUnderperformedStudents();
            break;

        case 7:
            indexCourse = readIndexCourse();
            printAverage(school, indexCourse);
            break;

        case 8:
            //exportDatabase();
            break;

        case 9:
            for (int level = 0; level < NUM_OF_LEVELES; level++) {
                for (int cls = 0; cls < NUM_OF_ClASSES; cls++)
                {
                    freeListNode(school[level][cls]);
                }
            }
            break;
        default:
            printf("\nThere is no item with symbol \"%d\".Please enter a number between 1-10!\nPress any key to continue...",
                input);

            break;
        }
        while (getchar() != '\n');

    } while (input != 9);
}

int main()
{
    ListNode* school[NUM_OF_LEVELES][NUM_OF_ClASSES];

    for (int level = 0; level < NUM_OF_LEVELES; level++) {
        for (int cls = 0; cls < NUM_OF_ClASSES; cls++)
        {
            school[level][cls] = createListNode();
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

            Student* st = createStudent(items[0], items[1], items[2], level, cls);
            fillGrades(st, grade);
            school[level][cls] = addNode(school[level][cls], st);
        }

        fclose(file);

    }
    menu(school);


    return 0;
}
