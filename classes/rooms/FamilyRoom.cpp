#include "FamilyRoom.h"
using namespace std;

FamilyRoom::FamilyRoom(int number, ViewFromWindow *view) : Room(number, view) {}
string FamilyRoom::getInfo() const
{
    return (string)"Номер для семьи. Больше стандартного.";
}
float FamilyRoom::getDollarPrice() const
{
    return 78.5;
}
int FamilyRoom::getMaxCustomersCount() const
{
    return 7;
}