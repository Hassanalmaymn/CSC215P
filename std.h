typedef struct{
  int id;
  char name[25];
  float gpa;
}Student;

int save_students_data(char*, Student*, int);
Student* get_students_data(char*, int*);

Student enter_student_data();
void print_student_data(Student*);
