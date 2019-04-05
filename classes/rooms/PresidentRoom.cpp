#include "PresidentRoom.h"
using namespace std;

PresidentRoom::PresidentRoom(int number, ViewFromWindow *view) : Room(number, view) {}
string PresidentRoom::getInfo() const
{
    return (string)"Президентский номер. Состоит из нескольких спальных комнат, гостиной, кабинета, с несколькими ванными комнатами и туалетами";
}
float PresidentRoom::getDollarPrice() const
{
    return 450.0;
}
int PresidentRoom::getMaxCustomersCount() const
{
    return 8;
}