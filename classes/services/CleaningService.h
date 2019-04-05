#pragma once
#include "Service.h"

class CleaningService : public Service
{
public:
    virtual std::string getInfo() const;
    virtual float getDollarPrice() const;
};