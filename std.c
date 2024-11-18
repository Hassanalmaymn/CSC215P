#include <stdio.h>
#include <stdlib.h>
#include "std.h"

int save_students_data(char* fn, Student* slist, int num)
{
    FILE* fp;
    int i;

    if ((fp = fopen(fn, "w")))
    {
        fwrite(&num, sizeof(int), 1, fp);

        for (i = 0 ; i < num ; i++)
        {
            if (! fwrite(slist + i, sizeof(Student), 1, fp))
            {
                perror("Problem writing to file");
                fclose(fp);
                return -2;
            }
        }

        fclose(fp);

        return 0;
    }

    perror("File could not be opened.");

    return -1;
}

Student* get_students_data(char* fn, int* num)
{
    FILE* fp;
    Student* result;
    int i;

    if ((fp = fopen(fn, "r")))
    {
        fread(num, sizeof(int), 1, fp);
        result = (Student*)calloc(*num, sizeof(Student));

        for (i = 0; i < *num; i++)
        {
            if (! fread(result+i, sizeof(Student), 1, fp))
            {
                perror("Problem reading from file");
                fclose(fp);

                return NULL;
            }
        }

        fclose(fp);

        return result;
    }

    perror("File could not be opened.");

    return NULL;
}

Student enter_student_data()
{
    Student s;

    printf("Enter student's id:");
    scanf("%d", &(s.id));
    getchar();

    printf("Enter student's name:");
    fgets(s.name, 24, stdin);

    printf("Enter student's GPA:");
    scanf("%f", &(s.gpa));

    return s;
}

void print_student_data(Student* s)
{
    printf("\n-----------------\n");
    printf("Student's id: %d\n", s->id);
    printf("Student's name: %s", s->name);
    printf("Student's GPA: %.2f\n", s->gpa);
    printf("-----------------\n");
}
