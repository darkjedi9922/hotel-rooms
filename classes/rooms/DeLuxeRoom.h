#pragma once
#include "Room.h"

class DeLuxeRoom : public Room
{
public:
    DeLuxeRoom(int number, ViewFromWindow *view);
    virtual std::string getInfo() const;
    virtual float getDollarPrice() const;
    virtual int getMaxCustomersCount() const;
};