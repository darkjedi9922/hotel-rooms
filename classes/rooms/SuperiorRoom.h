#pragma once
#include "Room.h"

class SuperiorRoom : public Room
{
public:
    SuperiorRoom(int number, ViewFromWindow *view);
    virtual std::string getInfo() const;
    virtual float getDollarPrice() const;
    virtual int getMaxCustomersCount() const;
};