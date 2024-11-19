#include <stdio.h>
#include <stdlib.h>
#include "account.h"
int save_account_data(char *fn, Account *accountList, int num)
{
    FILE *fp;
    int i;

    if ((fp = fopen(fn, "w")))
    {
        fwrite(&num, sizeof(int), 1, fp);

        for (i = 0; i < num; i++)
        {
            if (!fwrite(accountList + i, sizeof(Account), 1, fp))
            {
                perror("Problem writing to file");
                fclose(fp);
                return -1;
            }
        }

        fclose(fp);

        return 0;
    }
}
Account enter_Account_information()
{
    Account a;

    printf("Enter account's id:");
    scanf("%d", &(a.id));
    getchar();

    printf("Enter account holder name:");
    fgets(a.holderName, 49, stdin);

    printf("Enter account holder email:");
    fgets(a.holderEmail, 69, stdin);
    a.balance = 0;

    return a;
}
void print_student_data(Account* a)
{
    printf("\n-----------------\n");
    printf("account's id: %ld\n", a->id);
    printf("account's holder name: %s", a->holderName);
    printf("account's holder email: %s", a->holderEmail);
    printf("account's balance: %lf", a->balance);
    printf("number of operations: %d\n", a->id);
    printf("-----------------\n");
}
Account* get_students_data(char* fn, int* num)
{
    FILE* fp;
    Account* result;
    int i;

    if ((fp = fopen(fn, "r")))
    {
        fread(num, sizeof(int), 1, fp);
        result = (Account*)calloc(*num, sizeof(Account));

        for (i = 0; i < *num; i++)
        {
            if (! fread(result+i, sizeof(Account), 1, fp))
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