#pragma once
#include <string>

class Service
{
public:
    virtual ~Service() {}
    virtual std::string getInfo() const = 0;
    virtual float getDollarPrice() const = 0;
};
