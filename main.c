#include "account.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *filename = "accounts.bin";
    while (1)
    {
        int choice;
        printf("####################################\n \n");
        printf("0.exit\n");
        printf("welcome to our bank system \n");
        printf("here is the menu choose from 1-7\n");
        printf("1.Add acount.\n");
        printf("2.Update Accoun.\n");
        printf("3.Delete Account\n");
        printf("4.Delete Holder Accounts\n");
        printf("5.Search Account\n");
        printf("6.Display All Accounts\n");
        printf("7.Add operation\n");
        printf("####################################\n \n");
        printf("your choice is:");
        scanf("%d", &choice);

        switch (choice)
        {
        case 0:
            exit(0);
            break;
        case 1:
            add_account(filename);
            break;
        case 2:
            update_account(filename);
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            search_for_account_by_id_user(filename);
            break;
        case 6:
            break;
        case 7:
            add_operation(filename);
            break;

        default:
            printf("invalid choice\n");
            break;
        }
    }

    return 0;
}