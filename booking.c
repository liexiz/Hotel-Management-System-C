#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "booking.h"
#include "room.h"


// ===== loadBookings function =====
Booking* loadBookings(const char *filename) {

FILE *bookingFile = fopen(filename, "r");
if (bookingFile == NULL) {
        printf("bookings.txt file cannot be opened!\n");
        return NULL;
    }

Booking *head = NULL;
Booking *current = NULL;
Booking *newNode;
Booking temp;// temporary struct to store data while reading

while (fscanf(bookingFile, "%d %d %d %d %f", &temp.bookingID, &temp.roomID, &temp.accountID,
                  &temp.nights, &temp.totalCost) == 5) {

   newNode = (Booking*)malloc(sizeof(Booking));
   if (newNode == NULL) {
    printf("Memory allocation failed!\n");
   fclose(bookingFile);
   return head;
   }
   *newNode = temp;
   newNode->next = NULL;
   if (head == NULL) {
   head = newNode;
   } 
   else {
   current = head;
   while (current->next != NULL)
   current = current->next;

   current->next = newNode;
   }
   }

   fclose(bookingFile);
   return head;
}
// ===== saveBookings function =====
void saveBookings(Booking *head, const char *filename) {

    FILE *bookingFile = fopen(filename, "w");

    if (bookingFile == NULL) {
        printf("Could not save bookings! Please try again.\n"
);
        return;
    }

    Booking *current = head;

    while (current != NULL) {

        fprintf(bookingFile, "%d %d %d %d %.2f\n",
                current->bookingID, current->roomID,
                current->accountID, current->nights,
                current->totalCost);

        current = current->next;
    }

    fclose(bookingFile);
}

// ===== createBooking function =====
Booking* createBooking(Booking *head, Room *rooms,
                       int accountID, int roomID, int nights) {

    Room *selectedRoom = findRoom(rooms,roomID);

    if (selectedRoom == NULL) {
        printf("Room does not exist!\n");
        return head;
    }

    if (selectedRoom->status != 'A') {
        printf("This room is currently unavailable!\n");
        return head;
    }

    if (nights <= 0) {
        printf(" number of nights is not valid!\n");
        return head;
    }

    Booking *newNode = (Booking*)malloc(sizeof(Booking));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return head;
    }

    // store the booking details in the new node
    newNode->roomID = roomID;
    newNode->accountID = accountID;
    newNode->nights = nights;
    newNode->totalCost = calculateTotalCost(selectedRoom->price, nights);
    newNode->next = NULL;

    // determine new bookingID
    int bookingCounter = 0;
    Booking *current = head;

    while (current != NULL) {
        bookingCounter = current->bookingID;
        current = current->next;
    }

    newNode->bookingID = bookingCounter + 1;

    // update room status
    updateRoomStatus(rooms, roomID, 'O');

    // insert new node
    if (head == NULL) {
        head = newNode;
    } else {
        current = head;
        while (current->next != NULL)
            current = current->next;

        current->next = newNode;
    }

    printf("Booking created successfully.\n");
    printf("Booking ID: %d\n", newNode->bookingID);
    printf("Total cost: %.2f\n", newNode->totalCost);

    return head;
}

// ===== cancelBooking function =====
Booking* cancelBooking(Booking *head, int bookingID, Room *rooms) {

    Booking *current = head;
    Booking *previous = NULL;

    while (current != NULL) {

        if (current->bookingID == bookingID) {

            updateRoomStatus(rooms, current->roomID, 'A');

            if (previous == NULL)
                head = current->next;
            else
                previous->next = current->next;

            free(current);

            printf("Booking has been cancelled successfully.\n");
            return head;
        }

        previous = current;
        current = current->next;
    }

    printf("Booking not found!\n");
    return head;
}

// ===== printUserBookings function =====
void printUserBookings(Booking *head, int accountID) {

    Booking *current = head;
    int found = 0;

printf("\n=============================================\n");
printf("              Your Bookings\n");
printf("=============================================\n\n");

// table header
printf(" %-10s | %-8s | %-8s | %-10s\n",
       "BookingID", "RoomID", "Nights", "Cost");
printf("-----------------------------------------------\n");

while (current != NULL) {
    if (current->accountID == accountID) {
        printf(" %-10d | %-8d | %-8d | %-10.2f\n",
               current->bookingID,
               current->roomID,
               current->nights,
               current->totalCost);
        found = 1;
    }
    current = current->next;
}

if (!found) {
    printf("No bookings found for this account.\n");
}

printf("=============================================\n");
}
// ===== calculateTotalCost function =====
float calculateTotalCost(float pricePerNight, int nights) {
    return pricePerNight * nights;
}

// ===== freeBookings function =====
void freeBookings(Booking *head) {

    Booking *temp;

    while (head != NULL) {
        temp = head->next;
        free(head);
        head = temp;
    }
} 
