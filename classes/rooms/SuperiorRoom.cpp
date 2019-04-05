#include "SuperiorRoom.h"
using namespace std;

SuperiorRoom::SuperiorRoom(int number, ViewFromWindow *view) : Room(number, view) {}
string SuperiorRoom::getInfo() const
{
    return (string)"Улучшенный. Больше стандартного";
}
float SuperiorRoom::getDollarPrice() const
{
    return 45.0;
}
int SuperiorRoom::getMaxCustomersCount() const
{
    return 6;
}