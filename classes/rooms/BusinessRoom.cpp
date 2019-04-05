#include "BusinessRoom.h"
using namespace std;

BusinessRoom::BusinessRoom(int number, ViewFromWindow *view) : Room(number, view) {}
string BusinessRoom::getInfo() const
{
    return (string)"Номер с большой площадью, компьютером и факсом, предназначенный для работы";
}
float BusinessRoom::getDollarPrice() const
{
    return 36.56;
}
int BusinessRoom::getMaxCustomersCount() const
{
    return 3;
}