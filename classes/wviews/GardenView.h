#pragma once
#include "ViewFromWindow.h"

class GardenView : public ViewFromWindow
{
public:
    virtual std::string getInfo() const;
};

