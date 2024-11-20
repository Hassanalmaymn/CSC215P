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
        if (!isalpha(*name)) {
            if(*name==' '){
                break;
            } // Check if the character is not a letter
            return 0; // Invalid name
        }
        name++; // Move to the next character
    }

    return 1; // Valid name
}

int check_of_valid_email(const char* email){
      int contain_at_symbol=0;
      int contain_dot_symbol=0;
      if (email == NULL || *email == '\0') { 
        return 0;
        // Invalid email
    }
     while (*email != '\0') {
        if(*email=='@'){
            contain_at_symbol+=1;
        }
        if(*email=='.'){
            contain_dot_symbol+=1;
        }
        email++;

     }
     if (contain_at_symbol>1)
     {
        contain_at_symbol=0;
     }
      if (contain_dot_symbol>1)
     {
        contain_dot_symbol=0;
     }
     


     return contain_at_symbol&&contain_dot_symbol;


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
    printf("enter account id to search for it :");
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
        printf("account with ID %ld not found.\n", idToFind);
    }

    fclose(file);
    return a;
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
    printf("name is not valid try again please the valid name should be alphabeteical with space other charecters not allowed\n");
    valid=0;
    }
    else{
        valid=1;
    }
    }while(!valid);
    int emailIsValid=1;
    do{
    printf("Enter account holder email:");
    fgets(a.holderEmail, 69, stdin);
    const char* email= a.holderEmail;
    int x=check_of_valid_email(email);
    if(!x){
        printf("email is not valid\n");
        emailIsValid=0;
    }
    else{
        emailIsValid=1;
    }
    }while(!emailIsValid);
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


