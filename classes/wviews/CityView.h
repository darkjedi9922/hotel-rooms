#pragma once
#include "ViewFromWindow.h"

class CityView : public ViewFromWindow
{
public:
    virtual std::string getInfo() const;
};

