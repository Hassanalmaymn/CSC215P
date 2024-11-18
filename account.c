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
    fgets(a.holderName, 24, stdin);

    printf("Enter account holder email:");
    fgets(a.holderEmail, 24, stdin);
    a.balance = 0;

    return a;
}