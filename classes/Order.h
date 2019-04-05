#pragma once
#include "Date.h"
#include "Customer.h"
#include "List.h"
#include "services\Service.h"

class Room;

class Order
{
public:
    enum State {Active, Closed, Canceled};
    Order(Room *room, const Date &start, int daysAmount);
	~Order();
    void close();
    void cancel();
    void deleteCustomers();
    void deleteServices();

	void addCustomer(Customer *customer);
	void addService(Service *service);
	void setRoom(Room *);
	void setDate(const Date &start, int daysAmount);
	void setStartDate(const Date &start);
	void setDaysAmount(int amount);

    List<Customer*>* getCustomerList() const;
    List<Service*>* getServiceList() const;
    Room* getRoom() const;
    Date& getStartDate() const;
    Date& getEndDate() const;
    int getDaysAmount() const;
    int getState() const;

    float countDollarScore() const;

private:
	List<Customer*> customers;
	List<Service*> services;
	Room *room;
    Date start;
	Date end;
	int daysAmount;
    int state;
};
