#include <stdio.h>
#include <stdlib.h>
#include "account.h"
int add_account(const char *fn)
{

    FILE *bf;
    Account a;

    printf("Enter account's id:");
    scanf("%ld", &(a.id));
    getchar();

    printf("Enter account holder name:");
    fgets(a.holderName, 49, stdin);

    printf("Enter account holder email:");
    fgets(a.holderEmail, 69, stdin);
    a.balance = 0;
    a.numberOfOperations = 0;

    bf = fopen(fn, "ab");

    if (bf == NULL)
    {
        perror("Problem writing to file");
        return -1;
    }

    fwrite(&a, sizeof(Account), 1, bf);

    fclose(bf);

    return 0;
}

void print_student_data(Account *a)
{
    printf("\n-----------------\n");
    printf("account's id: %ld\n", a->id);
    printf("account's holder name: %s", a->holderName);
    printf("account's holder email: %s", a->holderEmail);
    printf("account's balance: %lf", a->balance);
    printf("number of operations: %ld\n", a->id);
    printf("-----------------\n");
}
Account *get_students_data(char *fn, int *num)
{
    FILE *fp;
    Account *result;
    int i;

    if ((fp = fopen(fn, "rb")))
    {
        fread(num, sizeof(int), 1, fp);
        result = (Account *)calloc(*num, sizeof(Account));

        for (i = 0; i < *num; i++)
        {
            if (!fread(result + i, sizeof(Account), 1, fp))
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
Account search_for_account_by_id(char *bfn)
{
    FILE *file = fopen(bfn, "rb");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    long int idToFind;
    printf("enter account id to searc for it :");
    scanf("%ld", &idToFind);


    Account a;
    int isFound=0;

    while (fread(&a, sizeof(Account), 1, file)) {
        if (a.id == idToFind) {
            printf("account found:\n");
            printf("account ID: %ld\naccount holder's Name: %s\naccount holder's Name: %s\naccount balance :%lf\nnumber of account operations:%d\n", a.id, a.holderName,a.holderEmail,a.balance,a.numberOfOperations);
            isFound = 1;
            break;
        }
    }

    if (!isFound) {
        printf("Student with ID %ld not found.\n", idToFind);
    }

    fclose(file);
    return a;
}