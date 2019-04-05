#pragma once
#include "Room.h"

class StandardRoom : public Room
{
public:
    StandardRoom(int number, ViewFromWindow *view);
    virtual std::string getInfo() const;
    virtual float getDollarPrice() const;
    virtual int getMaxCustomersCount() const;
};