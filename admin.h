#ifndef _ADMIN_H
#define _ADMIN_H

#include "room.h"
#include "account.h"
#include "booking.h"

// ===== Functions =====
void adminMenu(Room **rooms, Account **accounts, Booking **bookings);
void viewAllRooms(Room *rooms);
void addNewRoom(Room **rooms);
void editRoom(Room *rooms, int roomID, float newPrice, int newCapacity);
void viewAllAccounts(Account *accounts);
void viewAllBookings(Booking *bookings, Account *accounts);

#endif
