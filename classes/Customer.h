#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

class Customer
{
public:
    Customer();
    Customer(const std::string &name, int age);
    std::string getName() const;
    void setName(const std::string &name);
    int getAge() const;
    void setAge(int age);

private:
    std::string name;
    int age;
};

#endif // CUSTOMER_H
