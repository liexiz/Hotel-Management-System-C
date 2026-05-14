#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "room.h"

// ===== loadRooms function =====
Room* loadRooms(const char *filename){

   FILE *roomsFile = fopen(filename,"r");
   
   if (roomsFile == NULL){
      printf("rooms.txt file cannot be opened!\n");
      return NULL;
   }
   
   Room *head = NULL;
   int IndexOfType;
   Room room;
   
   while (fscanf(roomsFile, "%d %d %d %f %c %d", &room.roomID, &IndexOfType, &room.capacity,
         &room.price, &room.status, &room.amenityCount) == 6 ){
         //it will continue only if fscanf has read 6 data successfully
         
         switch (IndexOfType){
            case 0:
               room.type = STANDARD;
               break;
            case 1:
               room.type = DELUXE;
               break;
            case 2:
            room.type = SUITE;
            break;
         }
         
         int i;
         for (i = 0; i < room.amenityCount; i++)
            fscanf(roomsFile, " %[^\n]", room.amenities[i]);
            
         room.next = NULL;
         addRoom(&head, room);
   }
   
   fclose(roomsFile);
   return head;
}

// ===== saveRooms function =====
void saveRooms(Room *head, const char *filename){
   FILE *roomsFile = fopen (filename, "w");
   
   if (roomsFile == NULL){
      printf("rooms.txt file cannot be opened!\n");
      return;
   }
   
   Room *current = head;
   
   while (current != NULL){
      fprintf(roomsFile, "%d %d %d %.2f %c %d\n", current -> roomID, current -> type,
             current -> capacity, current -> price, current -> status, current -> amenityCount);
             
      int i;
      for (i = 0; i < current -> amenityCount; i++)
         fprintf(roomsFile, "%s\n", current -> amenities[i]);
      
      current = current -> next;
   }
   
   fclose(roomsFile);
}

// ===== printRooms function =====
void printRooms(Room *head){
   printf("%-5s %-10s %-5s %-10s %-7s %s\n", "ID", "Type", "Cap", "Price", "Status", "Amenities");
   
   Room *current = head;
   
   while (current != NULL){
      char roomType [20];
      
      switch (current -> type){
         case STANDARD:
            strcpy(roomType, "STANDARD");
            break;
         case DELUXE:
            strcpy(roomType, "DELUXE");
            break;
         case SUITE:
            strcpy(roomType, "SUITE");
            break;
      }
      
      printf("%-5d %-10s %-5d %-10.2f %-7c", current -> roomID, roomType,
            current -> capacity, current -> price, current -> status);
      
      int i;
      for (i = 0; i < current -> amenityCount; i++){
         printf("%s", current->amenities[i]);

         // If it's NOT the last amenity it will print a comma and space
         if (i < current->amenityCount - 1)
            printf(", ");  
      }
      
      printf("\n");
      current = current -> next;
   }
}

// ===== findRoom function =====
Room* findRoom(Room *head, int roomID){
   Room *current = head;
   
   while (current != NULL){
      if (current -> roomID == roomID)
         return current;
      
      current = current -> next;
   }
   
   return NULL;
}

// ===== updateRoomStatus function =====
void updateRoomStatus(Room *head, int roomID, char newStatus){
   Room *room = findRoom (head, roomID);
   
   if (room == NULL){
      printf("The room that you are trying to update is not found!\n");
      return;
   }
      
   room -> status = newStatus;
}

// ===== addRoom function =====
void addRoom(Room **head, Room newRoom){
   Room *newRoomNode = (Room*)malloc(sizeof(Room));
   
   if (newRoomNode == NULL) {
    printf("Memory allocation failed!\n");
    return;
   }

   *newRoomNode = newRoom;
   newRoomNode -> next = NULL;
   
   if(*head == NULL)
      *head = newRoomNode;
   else {
      Room *current = *head;
      while (current -> next != NULL)
         current = current -> next;
         
      current -> next = newRoomNode;
   }
}

// ===== freeRooms function =====
void freeRooms(Room *head){
   Room *current = head;
   Room *tmp;
   while (current != NULL){
      tmp = current -> next;
      free (current);
      current = tmp;
   }
}