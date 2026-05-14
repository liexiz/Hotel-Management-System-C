#ifndef _ACCOUNT_H
#define _ACCOUNT_H
// ===== Structures =====
typedef struct Account {
int accountID;
char username[20];
int age;
char password[20]; // stored encrypted
int isAdmin; // 1 = Admin, 0 = Regular user
struct Account *next;
} Account;

// ===== Functions =====
Account* loadAccounts(const char *filename);
void saveAccounts(Account *head, const char *filename);
Account* registerAccount(Account *head, char *username, int age, char*password);
Account* login(Account *head, char *username, char *password);
void encryptPassword(char *password);
void decryptPassword(char *password);
void freeAccounts(Account *head);
#endif