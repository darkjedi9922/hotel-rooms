#pragma once
#include "Room.h"

class BusinessRoom : public Room
{
public:
    BusinessRoom(int number, ViewFromWindow *view);
    virtual std::string getInfo() const;
    virtual float getDollarPrice() const;
    virtual int getMaxCustomersCount() const;
};