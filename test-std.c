#include "std.c"

int main()
{
    Student slist[3], *sff;
    int i, count;

    for (i = 0 ; i < 3 ; i++)
        slist[i] = enter_student_data();

    save_students_data("std.dat", slist, 3);

    sff = get_students_data("std.dat", &count);

    for (i = 0 ; i < count; i++)
        print_student_data(sff+i);

    return 0;
}
