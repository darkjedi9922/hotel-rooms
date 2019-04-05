#pragma once
#include <string>

class ViewFromWindow
{
public:
    virtual ~ViewFromWindow() {} // без этого выдает предупреждения про абстрактный класс без виртуального деструктора
    virtual std::string getInfo() const = 0;
};

