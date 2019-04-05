#include "Room.h"
using namespace std;

Room::Room(int number, ViewFromWindow *view)
{
    setNumber(number);
    setViewFromWindow(view);
    busy = false;
    currentOrder = 0;
}
Room::~Room()
{
    while (!orders.isEmpty()) delete orders.takeFirst();
    delete view;
}
void Room::makeOrder(Order *order)
{
    if (orders.contains(order)) throw (string)"Этот заказ уже существует";
    if (isOrdered(order->getStartDate(), order->getDaysAmount())) throw (string)"Заказ на заданную дату уже существует";
    if (!order->getRoom()) order->setRoom(this);
    orders.pushBack(order);
}
void Room::settle(Order *order)
{
    if (currentOrder) throw (string)"Комната уже занята";
    if (!orders.contains(order)) makeOrder(order);
    currentOrder = order;
    busy = true;
}
void Room::unsettle()
{
    if (!currentOrder) throw (string)"Комната не занята";
    Order *order = currentOrder;
    currentOrder = nullptr;
    busy = false;
    order->close();
}
void Room::setViewFromWindow(ViewFromWindow *view)
{
    this->view = view;
}
void Room::setNumber(int number)
{
    this->number = number;
}
List<Order*>* Room::getOrderList() const
{
    return const_cast<List<Order*>*>(&orders);
}
ViewFromWindow* Room::getViewFromWindow() const
{
    return view;
}
Order* Room::getCurrentOrder() const
{
    return currentOrder;
}
int Room::getNumber() const
{
    return number;
}
bool Room::isBusy() const
{
    return busy;
}
bool Room::isOrdered(const Date &start, int daysAmount) const
{
    Date end = start;
    end.addDays(daysAmount);
    List<Order*>::Iterator it = orders.createIterator();
    while (it.hasItem())
    {
        if (it.getItem()->getState() == Order::Active)
        {
            Date *itemStart = &it.getItem()->getStartDate();
            Date *itemEnd = &it.getItem()->getEndDate();

            // если даты пересекаются, значит на заданную дату уже существует заказ
            if (!((start < *itemStart && end < *itemStart) || (start > *itemEnd && end > *itemEnd))) return true;
        }
        it.next();
    }
    return false;
}

