#pragma once
#include <string>
#include "../Order.h"
#include "../List.h"
#include "../wviews/ViewFromWindow.h"

class Room
{
public:
    Room(int number, ViewFromWindow *view);
    virtual ~Room();
    void makeOrder(Order *order);
    void settle(Order *order);
    void unsettle();
	void setViewFromWindow(ViewFromWindow *view);
    void setNumber(int number);
    List<Order*>* getOrderList() const;
    ViewFromWindow* getViewFromWindow() const;
    Order* getCurrentOrder() const;
    int getNumber() const;
    bool isBusy() const;
    bool isOrdered(const Date &start, int daysAmount) const;

    virtual std::string getInfo() const = 0;
    virtual float getDollarPrice() const = 0;
    virtual int getMaxCustomersCount() const = 0;

private:
    int number;
    bool busy;
    List<Order*> orders;
    Order *currentOrder;
	ViewFromWindow *view;
};