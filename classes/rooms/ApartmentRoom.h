#pragma once
#include "Room.h"

class ApartmentRoom : public Room
{
public:
    ApartmentRoom(int number, ViewFromWindow *view);
    virtual std::string getInfo() const;
    virtual float getDollarPrice() const;
    virtual int getMaxCustomersCount() const;
};