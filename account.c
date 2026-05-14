#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "account.h"

// ===== loadAccounts function =====
Account* loadAccounts(const char *filename){
   FILE *accountsFile = fopen(filename, "r");
   
   if (accountsFile == NULL){
      printf("accounts.txt file cannot be opened!\n");
      return NULL;
   }
   
   Account *head = NULL;
   Account temp;
   
   while (fscanf(accountsFile, "%d %19s %d %19s %d", &temp.accountID, temp.username, &temp.age,
          temp.password, &temp.isAdmin) == 5) {
          
          decryptPassword(temp.password);
          
          Account *newNode = (Account*)malloc(sizeof(Account));
          
          if (newNode == NULL) {
            printf("Memory allocation failed!\n");
            fclose(accountsFile);
            return head; 
        }
        
        *newNode = temp;
        newNode->next = NULL;
        
        if (head == NULL)
            head = newNode;
        else {
            Account *current = head;
            while (current->next != NULL)
                current = current->next;

            current->next = newNode;
        }
    }
    
    fclose(accountsFile);
    return head;
}

// ===== saveAccounts function =====
void saveAccounts(Account *head, const char *filename){
   FILE *accountsFile = fopen(filename, "w");
   
   if (accountsFile == NULL){
      printf("accounts.txt file cannot be opened!\n");
      return;
   }
   
   Account *current = head;
   
   while (current != NULL){
      char password[20];
      strcpy(password, current -> password);
      encryptPassword(password);
      
      fprintf(accountsFile, "%d %s %d %s %d\n", current -> accountID, current -> username,
              current -> age, password, current -> isAdmin);
              
      current = current -> next;
      
   }
   
   fclose(accountsFile);
}

// ===== registerAccount function =====
Account* registerAccount(Account *head, char *username, int age, char*password){

   if (age < 18){
      printf("Sorry, you must be 18 years old or older to register!\n");
      return head;
   }
   
   Account *current = head;
   int IDCount = 1;
   
   while (current != NULL){
      if (strcmp(current -> username, username) == 0){
         printf("Sorry, this username is already taken!\n");
         return head;
      }
      
      current = current -> next;
      IDCount++;
   }
   
   Account *newAccount = (Account*)malloc(sizeof(Account));
   
   if (newAccount == NULL) {
    printf("Memory allocation failed!\n");
    return head;
   }
   
   newAccount -> accountID = IDCount;
   strcpy(newAccount -> username, username);
   newAccount -> age = age;
   strcpy(newAccount -> password, password);
   newAccount -> isAdmin = 0;
   newAccount -> next = NULL;
   
   if (head == NULL)
      head = newAccount;
   else{
      current = head;
      while (current -> next != NULL)
         current = current -> next;
      
      current -> next = newAccount;
   }
   printf("Registration process was succesfull!\n");
   return head;
}

// ===== login function =====
Account* login(Account *head, char *username, char *password){
   Account *current = head;
   
   while (current != NULL){
      if (strcmp(current -> username, username) == 0 && strcmp(current -> password, password) ==0)
      return current;
      
      current = current -> next;
   }
   
   return NULL;
}

// ===== encryptPassword function =====
void encryptPassword(char *password){
   int i = 0;
   int PassLen = strlen(password);

    while (i < PassLen) {
        password[i] = (char)(password[i] + 3);
        i++;
    }
}

// ===== decryptPassword function =====
void decryptPassword(char *password){
    int i = 0; 
    int PassLen = strlen(password);

    while (i < PassLen) {
        password[i] = (char)(password[i] - 3);  
        i++; 
    }
}

// ===== freeAccounts function =====
void freeAccounts(Account *head){
   Account *current = head;
   Account *tmp;
   while (current != NULL){
      tmp = current -> next;
      free (current);
      current = tmp;
   }
}