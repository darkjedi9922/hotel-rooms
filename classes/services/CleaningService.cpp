#include "CleaningService.h"
using namespace std;

string CleaningService::getInfo() const
{
    return (string)"Ежедневная уборка";
}
float CleaningService::getDollarPrice() const
{
    return 15.0;
}