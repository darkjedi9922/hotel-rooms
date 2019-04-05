#ifndef HOTEL_H
#define HOTEL_H

#include "List.h"
#include "rooms/Room.h"

class Hotel
{
public:
    ~Hotel();
    void addRoom(Room* room);
    int countRooms() const;
    int countRooms(bool busy) const;
    List<Room*>* getRoomList() const;

private:
    List<Room*> rooms;
};

#endif // HOTEL_H
