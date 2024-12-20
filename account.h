typedef struct{
  char operationSymbol;
  double amount;

}operation;

typedef struct{
  long int id;
  char holderName[50];
  char holderEmail[70];
  double balance;
  int numberOfOperations;
  operation operations [150];
}Account;

int add_account(const char *fn);
Account search_for_account_by_id_user(char *bfn);
void display_all_accounts(const char *fn);
int delete_account(const char *fn);
int delete_holder_accounts(const char *fn);
void update_account(const char *filename);
void add_operation(const char *filename);