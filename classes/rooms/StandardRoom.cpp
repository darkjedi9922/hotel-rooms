#include "StandardRoom.h"
using namespace std;

StandardRoom::StandardRoom(int number, ViewFromWindow *view) : Room(number, view) {}
string StandardRoom::getInfo() const
{
    return (string)"Стандартный номер";
}
float StandardRoom::getDollarPrice() const
{
    return 20.0;
}
int StandardRoom::getMaxCustomersCount() const
{
    return 3;
}