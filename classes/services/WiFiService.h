#ifndef WIFISERVICE_H
#define WIFISERVICE_H

#include "Service.h"

class WiFiService : public Service
{
public:
    virtual std::string getInfo() const;
    virtual float getDollarPrice() const;
};

#endif // WIFISERVICE_H
