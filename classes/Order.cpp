#include "Order.h"
#include "rooms/Room.h"
#include "time.h"
#include <string>
using namespace std;

Order::Order(Room *room, const Date &start, int daysAmount)
{
    state = Active;
    this->room = 0;
    setDate(start, daysAmount);
    setRoom(room);
}
Order::~Order()
{
    deleteCustomers();
    deleteServices();
}
void Order::close()
{
    state = Closed;
    if (room->getCurrentOrder() == this) room->unsettle();
}
void Order::cancel()
{
    state = Canceled;
    if (room->getCurrentOrder() == this) room->unsettle();
}
void Order::deleteCustomers()
{
    while (!customers.isEmpty()) delete customers.takeFirst();
}
void Order::deleteServices()
{
    while (!services.isEmpty()) delete services.takeFirst();
}

void Order::addCustomer(Customer *customer)
{
    if (customers.countSize() == room->getMaxCustomersCount()) throw (string)"Количество клиентов переполнено";
	customers.pushBack(customer);
}
void Order::addService(Service *service)
{
	services.pushBack(service);
}
void Order::setRoom(Room *room)
{
    if (this->room != 0) throw (string)"Заказ уже привязан к комнате";
    this->room = room;
    room->makeOrder(this);
}
void Order::setStartDate(const Date &start)
{
    time_t tt = time(NULL);
    tm *current = localtime(&tt);
    Date currentDate(current->tm_mday, current->tm_mon + 1, current->tm_year + 1900);
    if (start < currentDate) throw (string)"Дата въезда меньше текущей";
	this->start = start;
}
void Order::setDate(const Date &start, int daysAmount)
{
	setStartDate(start);
	setDaysAmount(daysAmount);
}
void Order::setDaysAmount(int amount)
{
    if (amount < 1) throw (string)"Количество дней меньше 1";
	daysAmount = amount;
	end = start;
    end.addDays(amount - 1); // первый день уже не считаем
}

List<Customer*>* Order::getCustomerList() const
{
    return const_cast<List<Customer*>*>(&customers);
}
List<Service*>* Order::getServiceList() const
{
    return const_cast<List<Service*>*>(&services);
}
Room* Order::getRoom() const
{
	return room;
}
Date& Order::getStartDate() const
{
    return const_cast<Date&>(start);
}
Date& Order::getEndDate() const
{
    return const_cast<Date&>(end);
}
int Order::getDaysAmount() const
{
	return daysAmount;
}
int Order::getState() const
{
	return state;
}

float Order::countDollarScore() const
{
	float servicesScore = 0;
	List<Service*>::Iterator it = services.createIterator();
	while (it.hasItem())
	{
		servicesScore += it.getItem()->getDollarPrice();
		it.next();
	}

	return customers.countSize() * daysAmount * (room->getDollarPrice() + servicesScore);
}
