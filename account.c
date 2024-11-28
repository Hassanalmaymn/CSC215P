#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "account.h"
int check_for_valid_name(const char *name)
{
    // Ensure the name is not empty
    if (name == NULL || *name == '\0')
    {
        return 0;
        // Invalid name
    }

    // Check each character in the string
    while (*name != '\0')
    {
        if (!isalpha(*name))
        {
            if (*name == ' ')
            {
                break;
            } // Check if the character is not a letter
            return 0; // Invalid name
        }
        name++; // Move to the next character
    }

    return 1; // Valid name
}

int check_of_valid_email(const char *email)
{
    int contain_at_symbol = 0;
    int contain_dot_symbol = 0;
    if (email == NULL || *email == '\0')
    {
        return 0;
        // Invalid email
    }
    while (*email != '\0')
    {
        if (*email == '@')
        {
            contain_at_symbol += 1;
        }
        if (*email == '.')
        {
            contain_dot_symbol += 1;
        }
        email++;
    }
    if (contain_at_symbol > 1)
    {
        contain_at_symbol = 0;
    }
    if (contain_dot_symbol > 1)
    {
        contain_dot_symbol = 0;
    }

    return contain_at_symbol && contain_dot_symbol;
}
Account search_for_account_by_id_me(const char *bfn, long int idToFind)
{
    FILE *file = fopen(bfn, "rb");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    Account a;
    rewind(file);
    while (fread(&a, sizeof(Account), 1, file))
    {
        if (a.id == idToFind)
        {
            break;
        }
    }

    fclose(file);
    return a;
}
Account search_for_account_by_id_user(char *bfn)
{
    FILE *file = fopen(bfn, "rb");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    long int idToFind;
    printf("enter account id to search for it :");
    scanf("%ld", &idToFind);

    Account a;
    int isFound = 0;
    rewind(file);
    while (fread(&a, sizeof(Account), 1, file))
    {
        if (a.id == idToFind)
        {
            printf("account found:\n");
            printf("account ID: %ld\naccount holder's Name: %s\naccount holder's Email: %s\naccount balance :%lf\nnumber of account operations:%d\n", a.id, a.holderName, a.holderEmail, a.balance, a.numberOfOperations);
            isFound = 1;
            break;
        }
    }

    if (!isFound)
    {
        printf("account with ID %ld not found.\n", idToFind);
    }

    fclose(file);
    return a;
}
void add_operation(const char *filename)
{
    FILE *file = fopen(filename, "rb+");
    if (!file)
    {
        perror("Error opening file");
        return;
    }

    long int idToFind;
    printf("Enter the account number for the operation: ");
    scanf("%ld", &idToFind);

    Account account;
    int found = 0;
    long int position = 0;

    // Search for the account
    while (fread(&account, sizeof(Account), 1, file))
    {
        if (account.id == idToFind)
        {
            found = 1;
            break;
        }
        position++;
    }

    if (!found)
    {
        printf("Account with ID %ld not found.\n", idToFind);
        fclose(file);
        return;
    }

    // Get operation type and amount
    char operationType;
    double amount;
    printf("Enter the operation type (d for deposit, w for withdraw): ");
    getchar(); // Consume newline from previous input
    scanf("%c", &operationType);

    printf("Enter the amount: ");
    scanf("%lf", &amount);

    // Validate the amount
    // check_for_valid_amount
    if (amount <= 0)
    {
        printf("Invalid amount. Must be positive.\n");
        fclose(file);
        return;
    }

    // Perform the operation
    if (operationType == 'd')
    {
        account.balance += amount;
    }
    else if (operationType == 'w')
    {
        if (account.balance < amount)
        {
            printf("Insufficient balance for withdrawal.\n");
            fclose(file);
            return;
        }
        account.balance -= amount;
    }
    else
    {
        printf("Invalid operation type. Use 'd' for deposit or 'w' for withdraw.\n");
        fclose(file);
        return;
    }

    // Add the operation to the operations array
    if (account.numberOfOperations < 150)
    {
        account.operations[account.numberOfOperations].operationSymbol = operationType;
        account.operations[account.numberOfOperations].amount = amount;
        account.numberOfOperations++;
    }
    else
    {
        printf("Operation limit reached for this account.\n");
        fclose(file);
        return;
    }

    // Write back the updated account
    fseek(file, position * sizeof(Account), SEEK_SET);
    fwrite(&account, sizeof(Account), 1, file);

    printf("Operation completed successfully.\n");

    fclose(file);
}

// Function to update an account
void update_account(const char *filename)
{
    FILE *file = fopen(filename, "rb+");
    if (!file)
    {
        perror("Error opening file");
        return;
    }

    long int idToUpdate;
    printf("Enter the account number to update: ");
    scanf("%ld", &idToUpdate);

    Account account;
    int found = 0;
    long int position = 0;

    // Search for the account
    while (fread(&account, sizeof(Account), 1, file))
    {
        if (account.id == idToUpdate)
        {
            found = 1;
            break;
        }
        position++;
    }

    if (!found)
    {
        printf("Account with ID %ld not found.\n", idToUpdate);
        fclose(file);
        return;
    }

    // Options for updates
    int choice;
    printf("What would you like to update?\n");
    printf("1. Account Number\n");
    printf("2. Holder Name\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    // Update account number
    if (choice == 1)
    {
        long int newId;
        int isUnique = 0;

        do
        {
            printf("Enter the new account number: ");
            scanf("%ld", &newId);

            // Check if the new ID is unique
            rewind(file); // Go back to the beginning of the file
            Account temp;
            isUnique = 1;

            while (fread(&temp, sizeof(Account), 1, file))
            {
                if (temp.id == newId)
                {
                    printf("This account number already exists. Try again.\n");
                    isUnique = 0;
                    break;
                }
            }
        } while (!isUnique);

        account.id = newId;
    }

    // Update holder name
    else if (choice == 2)
    {
        char newName[50];
        int valid;

        do
        {
            printf("Enter the new holder name: ");
            getchar(); // To consume newline from previous input
            fgets(newName, sizeof(newName), stdin);
            newName[strcspn(newName, "\n")] = '\0'; // Remove newline character

            valid = check_for_valid_name(newName);
            if (!valid)
            {
                printf("Invalid name. The name must contain only alphabetic characters and spaces. Try again.\n");
            }
        } while (!valid);

        strcpy(account.holderName, newName);
    }

    // Write back the updated account
    fseek(file, position * sizeof(Account), SEEK_SET);
    fwrite(&account, sizeof(Account), 1, file);

    printf("Account updated successfully.\n");

    fclose(file);
}
int delete_holder_accounts(const char *fn)
{
    char holderName[50];
    int c; // To clear input buffer

    printf("Enter account holder name to delete all their accounts: ");

    // Clear the input buffer to avoid issues with fgets
    while ((c = getchar()) != '\n' && c != EOF)
        ;

    fgets(holderName, sizeof(holderName), stdin);
    holderName[strcspn(holderName, "\n")] = '\0';

    int valid = check_for_valid_name(holderName);
    if (!valid)
    {
        printf("Invalid name. Holder name must contain only alphabetical characters.\n");
        return -2;
    }

    FILE *file = fopen(fn, "rb");
    if (file == NULL)
    {
        perror("Error opening file");
        return -1;
    }

    FILE *tempFile = fopen("temp.bin", "wb");
    if (tempFile == NULL)
    {
        perror("Error creating temporary file");
        fclose(file);
        return -1;
    }

    Account account;
    int found = 0;

    // Read each account and write to temp file if it doesn't match the holder name
    while (fread(&account, sizeof(Account), 1, file))
    {
        if (strcmp(account.holderName, holderName) == 0)
        {
            found = 1; // Mark as found if the holder name matches
        }
        else
        {
            fwrite(&account, sizeof(Account), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (remove(fn) != 0 || rename("temp.bin", fn) != 0)
    {
        perror("Error updating file");
        return -1;
    }

    if (found)
    {
        printf("All accounts for holder '%s' deleted successfully.\n", holderName);
        return 0;
    }
    else
    {
        printf("No accounts found for holder '%s'.\n", holderName);
        return -2;
    }
}
void display_all_accounts(const char *fn)
{
    FILE *file = fopen(fn, "rb");
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }

    Account account;
    int isEmpty = 1;

    printf("\n======= All Accounts =======\n");

    // Read and display all accounts
    while (fread(&account, sizeof(Account), 1, file))
    {
        isEmpty = 0; // Mark as not empty if at least one account exists
        printf("Account ID: %ld\n", account.id);
        printf("Holder Name: %s\n", account.holderName);
        printf("Holder Email: %s\n", account.holderEmail);
        printf("Balance: %.2lf\n", account.balance);
        printf("Number of Operations: %d\n", account.numberOfOperations);
        printf("-----------------------------\n");
    }

    if (isEmpty)
    {
        printf("No accounts found in the system.\n");
    }

    fclose(file);
}
int delete_account(const char *fn)
{
    long int idToDelete;
    printf("Enter account id to delete: ");
    scanf("%ld", &idToDelete);

    FILE *file = fopen(fn, "rb");
    if (file == NULL)
    {
        perror("Error opening file");
        return -1;
    }

    FILE *tempFile = fopen("temp.bin", "wb");
    if (tempFile == NULL)
    {
        perror("Error creating temporary file");
        fclose(file);
        return -1;
    }

    Account account;
    int found = 0;

    // Read each account and write to temp file if it doesn't match the ID
    while (fread(&account, sizeof(Account), 1, file))
    {
        if (account.id == idToDelete)
        {
            found = 1; // Mark account as found
        }
        else
        {
            fwrite(&account, sizeof(Account), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    // Replace the original file with the temporary file
    if (remove(fn) != 0 || rename("temp.bin", fn) != 0)
    {
        perror("Error updating file");
        return -1;
    }

    if (found)
    {
        printf("Account with ID %ld deleted successfully.\n", idToDelete);
        return 0;
    }
    else
    {
        printf("Account with ID %ld not found.\n", idToDelete);
        return -2;
    }
}
int add_account(const char *fn)
{

    FILE *bf;
    Account a;

    printf("Enter account id:");
    scanf("%ld", &(a.id));
    getchar();
    long int idToFind;
    FILE *file = fopen(fn, "rb");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    idToFind = a.id;
    Account temp;

    while (fread(&temp, sizeof(Account), 1, file))
    {
        if (temp.id == idToFind)
        {
            printf("account is already exsists!\n");
            return -2;
        }
    }

    fclose(file);

    int valid = 1;
    do
    {
        printf("Enter account holder name:");
        fgets(a.holderName, 49, stdin);
        const char *name = a.holderName;
        a.holderName[strcspn(a.holderName, "\n")] = '\0';
        int x = check_for_valid_name(name);
        if (!x)
        {
            printf("name is not valid try again please the valid name should be alphabeteical with space other charecters not allowed\n");
            valid = 0;
        }
        else
        {
            valid = 1;
        }
    } while (!valid);
    int emailIsValid = 1;
    do
    {
        printf("Enter account holder email:");
        fgets(a.holderEmail, 69, stdin);
        const char *email = a.holderEmail;
        int x = check_of_valid_email(email);
        if (!x)
        {
            printf("email is not valid\n");
            emailIsValid = 0;
        }
        else
        {
            emailIsValid = 1;
        }
    } while (!emailIsValid);
    a.balance = 0;
    a.numberOfOperations = 0;

    bf = fopen(fn, "ab");

    if (bf == NULL)
    {
        perror("Problem writing to file");
        return -1;
    }

    fwrite(&a, sizeof(Account), 1, bf);
    fflush(bf);
    fclose(bf);

    printf("account added successfully \n");
    return 0;
}
