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
 operation operations [];
}Account;
