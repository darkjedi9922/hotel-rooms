#pragma once
#include "Room.h"

class PresidentRoom : public Room
{
public:
    PresidentRoom(int number, ViewFromWindow *view);
    virtual std::string getInfo() const;
    virtual float getDollarPrice() const;
    virtual int getMaxCustomersCount() const;
};