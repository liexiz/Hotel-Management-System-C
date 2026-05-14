#ifndef _ROOM_H
#define _ROOM_H
// ===== Structures =====
typedef enum {
STANDARD,
DELUXE,
SUITE
} RoomType;

typedef struct Room {
int roomID;
RoomType type;
int capacity;
float price;
char status; // 'A' = Available, 'O' = Occupied
char amenities[5][20];
int amenityCount;
struct Room *next; // linked list pointer
} Room;

// ===== Functions =====
Room* loadRooms(const char *filename);
void saveRooms(Room *head, const char *filename);
void printRooms(Room *head);
Room* findRoom(Room *head, int roomID);
void updateRoomStatus(Room *head, int roomID, char newStatus);
void addRoom(Room **head, Room newRoom);
void freeRooms(Room *head);
#endif