#ifndef FOODDELIVERYSERVICE_H
#define FOODDELIVERYSERVICE_H

#include "Service.h"

class FoodDeliveryService : public Service
{
public:
    virtual std::string getInfo() const;
    virtual float getDollarPrice() const;
};

#endif // FOODDELIVERYSERVICE_H
