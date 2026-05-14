#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "account.h"
#include "account.c"
#include "booking.h"
#include "booking.c"
#include "admin.h"
#include "admin.c"
#include "room.c"

void printOnlyAvailableRooms(Room *rooms); 
int main() {
char username[21], password[21];
int age;
int roomID, nights;
int bookingID;
//3 linked list to Load data from files
Room *rooms = loadRooms("rooms.txt");
Account *accounts = loadAccounts("accounts.txt");
Booking *bookings = loadBookings("bookings.txt");

Account *currentUser ; 
int choice;

printf("\n=========================================\n");
printf("        Hotel Management System       \n");
printf("=========================================\n");

do {
    printf("\n-------------- Main Menu --------------\n");
    printf("  1) Register\n");
    printf("  2) Login\n");
    printf("  3) Exit\n");
    printf("----------------------------------------\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
switch (choice) {

//Register main menu============================================ 
case 1 : 
//char username[21], password[21];
//int age;
printf("Enter username: ");
scanf(" %[^\n]", username);

printf("Enter age: ");
scanf("%d", &age);

printf("Enter password: ");
scanf("%s", password);

accounts = registerAccount(accounts, username, age, password);
break;
//Login main menu================================================== 
case 2: 
printf("Enter username: ");
scanf("%s", username);

printf("Enter password: ");
scanf("%s", password);

currentUser = login(accounts, username, password);
if (currentUser == NULL) {                       
printf("Login failed! Please check your login details\n");
break; 
}
//the admin menu
if( currentUser->isAdmin == 1  ) {   
adminMenu(&rooms, &accounts, &bookings);
break; 
}

//user menu
int userChoice = 0 ; 
while( userChoice != 5 ){
printf("\n-------------- User Menu --------------\n");
printf("  1) View Available Rooms\n");
printf("  2) Book a Room\n");
printf("  3) Cancel a Booking\n");
printf("  4) View My Bookings\n");
printf("  5) Logout\n");
printf("----------------------------------------\n");
printf("Enter your choice: ");
scanf("%d", &userChoice);
switch (userChoice) {

// View Available Rooms by calling the method
case 1: 
printOnlyAvailableRooms(rooms); 
break;

// Booking a Room
case 2:
//int roomID, nights;
printf("Enter the Room ID for your booking :");
scanf("%d", &roomID);
printf("Enter number of nights : ");
scanf("%d", &nights);

bookings = createBooking(bookings, rooms, currentUser->accountID,roomID, nights);
break;

// Cancel a Booking
case 3:
//int bookingID;
printf("Enter the Booking ID you want to cancel: ");
scanf("%d", &bookingID);
bookings = cancelBooking(bookings, bookingID, rooms);
break;

// View user Bookings
case 4: 
printUserBookings(bookings, currentUser->accountID);
break;

// Logout
case 5: 
printf("Logout complete.\n");
break;
default:
printf("Invalid selection!\n");
}// end userChoice switch

} // while userChoice
break;  // end login case 

// Exit================================================
case 3: 
printf("Saving your data ... exiting now\n");
//save
saveRooms(rooms, "rooms.txt");
saveAccounts(accounts, "accounts.txt");
saveBookings(bookings, "bookings.txt");
//free
freeRooms(rooms);
freeAccounts(accounts);
freeBookings(bookings);
break;

default:
printf("Invalid choice!\n");
} // switch

}while( choice != 3 ); 
return 0;
}//end main*********************************************


void printOnlyAvailableRooms(Room *rooms){
printf("\n-------- Available Rooms --------\n");
printf("%-5s | %-10s | %-5s | %-10s | %-7s | %s\n",
       "ID","Type","Cap","Price","Status","Amenities");
printf("---------------------------------------------------------------\n");

Room *current = rooms;
while(current != NULL){
   if(current->status == 'A'){
   char typeStr[20];
   switch(current->type){
    case STANDARD: strcpy(typeStr,"STANDARD"); break;
    case DELUXE:   strcpy(typeStr,"DELUXE");   break;
    case SUITE:    strcpy(typeStr,"SUITE");    break;
   }
printf("%-5d | %-10s | %-5d | %-10.2f | %-7c | ",
     current->roomID, typeStr, current->capacity,
     current->price, current->status);

    for(int i=0;i<current->amenityCount;i++){
    printf("%s", current->amenities[i]);
     if(i < current->amenityCount - 1) printf(", ");
     }
 printf("\n");
   }
    current = current->next;
    }
}
