#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admin.h"

//admin Menu
void adminMenu(Room **rooms, Account **accounts, Booking **bookings){
int choice;
do {
printf("\n================================\n");
printf("           Admin Menu           \n");
printf("================================\n");
printf("  1) Show all rooms\n");
printf("  2) Add a room\n");
printf("  3) Modify a room\n");
printf("  4) Show all accounts\n");
printf("  5) Show all bookings\n");
printf("  6) Back to main menu\n");
printf("================================\n");
printf("Enter your choice : ");

scanf("%d", &choice);
//each case called method 
switch (choice) {

case 1:
viewAllRooms(*rooms);
break;

 case 2:
addNewRoom(rooms);
break;

case 3: {
int idToChange;
float priceUpdate;
int capacityUpdate;

printf("Room ID to edit: ");
scanf("%d", &idToChange);

printf("New price: ");
scanf("%f", &priceUpdate);

printf("New capacity: ");
scanf("%d", &capacityUpdate);

editRoom(*rooms, idToChange, priceUpdate, capacityUpdate);
break;
}

case 4:
viewAllAccounts(*accounts);
break;

case 5:
viewAllBookings(*bookings, *accounts);
break;

case 6:
printf("Going back to the main menu...\n");
break;

default:
printf("Option not available. Try again.\n");
}
} while (choice != 6);
}

//the methods
//============================================================================
void viewAllRooms(Room *rooms) {
printRooms(rooms);
}
//============================================================================
void addNewRoom(Room **rooms) {
Room newEntry;

printf("\n--- Add New Room ---\n");

printf("Enter room ID: ");
scanf("%d", &newEntry.roomID);

printf("Select room type [0 = STANDARD, 1 = DELUXE, 2 = SUITE]: ");
int typeInput;
scanf("%d", &typeInput);
newEntry.type = (RoomType)typeInput;

printf("Enter room capacity: ");
scanf("%d", &newEntry.capacity);

printf("Enter price: ");
scanf("%f", &newEntry.price);

newEntry.status = 'A';  // A = Available

printf("Enter number of amenities: ");
scanf("%d", &newEntry.amenityCount);

for (int i = 0; i < newEntry.amenityCount; i++) {
    printf("Amenity #%d: ", i + 1);
    scanf("%s", newEntry.amenities[i]);
}

newEntry.next = NULL;
addRoom(rooms, newEntry);

printf("\nRoom added successfully.\n");
printf("------------------------\n");

}
//============================================================================
void editRoom(Room *rooms, int roomID, float newPrice, int newCapacity) {
Room *room = findRoom(rooms, roomID);
if (room != NULL) {
room->price = newPrice;
room->capacity = newCapacity;
   printf("Room details have been updated.\n"); }
else
    printf("No room found with this ID.\n");
 
}//end method
//============================================================================

void viewAllAccounts(Account *accounts) {

printf("\n--- Account List ---\n");
printf("%-10s | %-15s | %-5s | %-10s\n",
        "ID", "Username", "Age", "Type");
printf("------------------------------------------------\n");
Account *current = accounts;
while (current != NULL) {
printf("%-10d | %-15s | %-5d | %-10s\n",
   current->accountID,
   current->username,
   current->age,
   current->isAdmin ? "Admin" : "User");
   current = current->next;
    } // end while
} // end method

//============================================================================

void viewAllBookings(Booking *bookings, Account *accounts) {
printf("\n--- Booking List ---\n");
printf("%-10s | %-10s | %-15s | %-8s | %-10s\n",
       "BookingID", "RoomID", "Username", "Nights", "TotalCost");
printf("-------------------------------------------------------------\n");
Booking *current = bookings;
while (current != NULL) {
char username[20] = "Unknown";
Account *acc = accounts;
   while (acc != NULL) {
   if (acc->accountID == current->accountID) {
    strcpy(username, acc->username);
    break;
    }
   acc = acc->next;
   }
    printf("%-10d | %-10d | %-15s | %-8d | %-10.2f\n",
               current->bookingID,
               current->roomID,
               username,
               current->nights,
               current->totalCost);
current = current->next;
    } // end while
} // end method
