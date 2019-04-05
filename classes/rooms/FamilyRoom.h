#pragma once
#include "Room.h"

class FamilyRoom : public Room
{
public:
    FamilyRoom(int number, ViewFromWindow *view);
    virtual std::string getInfo() const;
    virtual float getDollarPrice() const;
    virtual int getMaxCustomersCount() const;
};