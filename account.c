#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "account.h"
    int check_for_valid_name(const char *name) {
    // Ensure the name is not empty
    if (name == NULL || *name == '\0') { 
        return 0;
        // Invalid name
    }

    // Check each character in the string
    while (*name != '\0') {
        if (!isalpha(*name)) { // Check if the character is not a letter
            return 0; // Invalid name
        }
        name++; // Move to the next character
    }

    return 1; // Valid name
}


Account search_for_account_by_id_me( const char *bfn,long int idToFind)
{
    FILE *file = fopen(bfn, "rb");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    Account a;

    while (fread(&a, sizeof(Account), 1, file)) {
        if (a.id == idToFind) {
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
    printf("enter account id to searc for it :");
    scanf("%ld", &idToFind);


    Account a;
    int isFound=0;

    while (fread(&a, sizeof(Account), 1, file)) {
        if (a.id == idToFind) {
            printf("account found:\n");
            printf("account ID: %ld\naccount holder's Name: %s\naccount holder's Email: %s\naccount balance :%lf\nnumber of account operations:%d\n", a.id, a.holderName,a.holderEmail,a.balance,a.numberOfOperations);
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
int add_account(const char *fn)
{

    FILE *bf;
    Account a;

    printf("Enter account's id:");
    scanf("%ld", &(a.id));
    getchar();
    long int idToFind;
    FILE *file = fopen(fn, "rb");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    idToFind=a.id;
    Account temp;

    while (fread(&temp, sizeof(Account), 1, file)) {
        if (temp.id == idToFind) {
            printf("account is already exsists!\n");
            return -2;
        }
    }

    fclose(file);
    
    int valid=1;
    do{
    printf("Enter account holder name:");
    fgets(a.holderName, 49, stdin);
    const char* name=a.holderName;
    a.holderName[strcspn(a.holderName, "\n")] = '\0';
    int x=check_for_valid_name(name);
    if(!x){
    printf("name is not valid try again\n");
    valid=0;
    }
    else{
        valid=1;
    }
    }while(!valid);
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

    printf("account added successfully \n");
    return 0;
}


