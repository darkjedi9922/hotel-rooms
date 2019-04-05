#include "ApartmentRoom.h"
using namespace std;

ApartmentRoom::ApartmentRoom(int number, ViewFromWindow *view) : Room(number, view) {}
string ApartmentRoom::getInfo() const
{
    return (string)"Апартаменты, аналог квартиры. Состоит из нескольких комнат и кухни";
}
float ApartmentRoom::getDollarPrice() const
{
    return 60.0;
}
int ApartmentRoom::getMaxCustomersCount() const
{
    return 4;
}