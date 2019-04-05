#include "Hotel.h"
using namespace std;

Hotel::~Hotel()
{
    while (!rooms.isEmpty()) delete rooms.takeFirst();
}
void Hotel::addRoom(Room *room)
{
    rooms.pushBack(room);
}
int Hotel::countRooms() const
{
    return rooms.countSize();
}
int Hotel::countRooms(bool busy) const
{
    int size = 0;
    List<Room*>::Iterator it = rooms.createIterator();
    while (it.hasItem())
    {
        if (it.getItem()->isBusy() == busy) size++;
        it.next();
    }
    return size;
}
List<Room*>* Hotel::getRoomList() const
{
    return const_cast<List<Room*>*>(&rooms);
}
