#include "DeLuxeRoom.h"
using namespace std;

DeLuxeRoom::DeLuxeRoom(int number, ViewFromWindow *view) : Room(number, view) {}
string DeLuxeRoom::getInfo() const
{
    return (string)"Однокомнатный номер большого размера с дорогой обстановкой";
}
float DeLuxeRoom::getDollarPrice() const
{
    return 120.0;
}
int DeLuxeRoom::getMaxCustomersCount() const
{
    return 2;
}