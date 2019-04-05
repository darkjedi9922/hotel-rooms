#include "Customer.h"
using namespace std;

Customer::Customer()
{
    name = "";
    age = 0;
}
Customer::Customer(const string &name, int age)
{
    setName(name);
    setAge(age);
}
string Customer::getName() const
{
    return name;
}
void Customer::setName(const string &name)
{
    this->name = name;
}
int Customer::getAge() const
{
    return age;
}
void Customer::setAge(int age)
{
    if (age < 0) throw (string)"Возраст не может быть меньше 0";
    this->age = age;
}
