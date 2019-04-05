#include "MainWindow.h"
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#include "classes/rooms/StandardRoom.h"
#include "classes/rooms/ApartmentRoom.h"
#include "classes/rooms/BusinessRoom.h"
#include "classes/rooms/DeLuxeRoom.h"
#include "classes/rooms/FamilyRoom.h"
#include "classes/rooms/SuperiorRoom.h"
#include "classes/rooms/PresidentRoom.h"

#include "classes/wviews/GardenView.h"
#include "classes/wviews/BeachView.h"
#include "classes/wviews/CityView.h"

#include "classes/services/CleaningService.h"
#include "classes/services/FoodDeliveryService.h"
#include "classes/services/WiFiService.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadData();

    updateCounters();

    List<Room*>::Iterator it = hotel.getRoomList()->createIterator();
    while (it.hasItem())
    {
        RoomListItem *item = new RoomListItem(it.getItem(), this);
        ui->widget->layout()->addWidget(item);
        QObject::connect(item, SIGNAL(mouseReleased()), this, SLOT(roomClicked()));
        it.next();
    }
}
MainWindow::~MainWindow()
{
    saveData();
    delete ui;
}
void MainWindow::loadData()
{
    QFile xml("data.xml");
    if (xml.open(QFile::ReadOnly | QFile::Text))
    {
        QXmlStreamReader reader;
        reader.setDevice(&xml);

        Room *room = 0;
        Order *order = 0;
        do {
            reader.readNext();
            if (reader.isStartElement())
            {
                // Проходимся по имени тега
                if (reader.name() == "room") {
                    // По третьему атрибуту определяем вид из окна
                    ViewFromWindow *view;
                    QStringRef attr2 = reader.attributes().at(2).value();
                    if (attr2 == "garden") view = new GardenView;
                    else if (attr2 == "beach") view = new BeachView;
                    else if (attr2 == "city") view = new CityView;
                    else throw "The view is not exist.";
                    // Затем по второму определяем тип комнаты и создаем ее
                    int number = reader.attributes().at(0).value().toInt();
                    QStringRef attr1 = reader.attributes().at(1).value();
                    if (attr1 == "standard") room = new StandardRoom(number, view);
                    else if (attr1 == "apartment") room = new ApartmentRoom(number, view);
                    else if (attr1 == "business") room = new BusinessRoom(number, view);
                    else if (attr1 == "deluxe") room = new DeLuxeRoom(number, view);
                    else if (attr1 == "family") room = new FamilyRoom(number, view);
                    else if (attr1 == "superior") room = new SuperiorRoom(number, view);
                    else if (attr1 == "president") room = new PresidentRoom(number, view);
                    else throw "The type of room is not exist.";
                    hotel.addRoom(room);
                }
                else if (reader.name() == "order")
                {
                    order = new Order(room,
                                      Date(reader.attributes().at(0).value().toInt(),
                                           reader.attributes().at(1).value().toInt(),
                                           reader.attributes().at(2).value().toInt()),
                                      reader.attributes().at(3).value().toInt());
                    int state = reader.attributes().at(4).value().toInt();
                    if (state == Order::Canceled) order->cancel();
                    else if (state == Order::Closed) order->close();
                    if (reader.attributes().at(5).value() == "1") room->settle(order);
                }
                else if (reader.name() == "customer")
                {
                    order->addCustomer(new Customer(reader.attributes().at(0).value().toString().toStdString(), reader.attributes().at(1).value().toInt()));
                }
                else if (reader.name() == "service")
                {
                    Service *service = 0;
                    if (reader.attributes().at(0).value() == "cleaning") service = new CleaningService;
                    else if (reader.attributes().at(0).value() == "food") service = new FoodDeliveryService;
                    else if (reader.attributes().at(0).value() == "wifi") service = new WiFiService;
                    order->addService(service);
                }
            }
        }
        while (!reader.atEnd());
        xml.close();
    }
    else throw "File open error.";
}
void MainWindow::saveData()
{
    QFile xml("data.xml");
    xml.open(QFile::WriteOnly);
    QXmlStreamWriter writer(&xml);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("hotel");
    // Проходимся по всем комнатам
    auto it = hotel.getRoomList()->createIterator();
    while (it.hasItem())
    {
        // Записываем комнату
        Room *room = it.getItem();
        writer.writeStartElement("room");
        writer.writeAttribute("number", QString::number(room->getNumber()));
        // Определяем и записываем тип комнаты
        QString type;
        if (dynamic_cast<StandardRoom*>(room)) type = "standard";
        else if (dynamic_cast<ApartmentRoom*>(room)) type = "apartment";
        else if (dynamic_cast<BusinessRoom*>(room)) type = "business";
        else if (dynamic_cast<DeLuxeRoom*>(room)) type = "deluxe";
        else if (dynamic_cast<FamilyRoom*>(room)) type = "family";
        else if (dynamic_cast<SuperiorRoom*>(room)) type = "superior";
        else if (dynamic_cast<PresidentRoom*>(room)) type = "president";
        else throw "The type of room is not exist.";
        writer.writeAttribute("type", type);
        // Определяем и записываем тип вида из окна
        ViewFromWindow *view = room->getViewFromWindow();
        if (dynamic_cast<GardenView*>(view)) type = "garden";
        else if (dynamic_cast<BeachView*>(view)) type = "beach";
        else if (dynamic_cast<CityView*>(view)) type = "city";
        else throw "The type of view from widnow is not exist.";
        writer.writeAttribute("view", type);
        // Проходимся по заказам комнаты
        auto oIt = room->getOrderList()->createIterator();
        while (oIt.hasItem())
        {
            // Записываем основное по заказу
            writer.writeStartElement("order");
            writer.writeAttribute("startDay", QString::number(oIt.getItem()->getStartDate().getDay()));
            writer.writeAttribute("startMonth", QString::number(oIt.getItem()->getStartDate().getMonth()));
            writer.writeAttribute("startYear", QString::number(oIt.getItem()->getStartDate().getYear()));
            writer.writeAttribute("days", QString::number(oIt.getItem()->getDaysAmount()));
            writer.writeAttribute("state", QString::number(oIt.getItem()->getState()));
            if (oIt.getItem() == it.getItem()->getCurrentOrder()) writer.writeAttribute("current", "1");
            else writer.writeAttribute("current", "0");
            // Клиенты
            auto cIt = oIt.getItem()->getCustomerList()->createIterator();
            while (cIt.hasItem())
            {
                writer.writeStartElement("customer");
                writer.writeAttribute("name", QString::fromStdString(cIt.getItem()->getName()));
                writer.writeAttribute("age", QString::number(cIt.getItem()->getAge()));
                writer.writeEndElement(); // customer
                cIt.next();
            }
            // Услуги
            auto sIt = oIt.getItem()->getServiceList()->createIterator();
            while (sIt.hasItem())
            {
                // Определяем тип
                Service *service = sIt.getItem();
                if (dynamic_cast<CleaningService*>(service)) type = "cleaning";
                else if (dynamic_cast<FoodDeliveryService*>(service)) type = "food";
                else if (dynamic_cast<WiFiService*>(service)) type = "wifi";
                else throw "The type of service is not exist.";
                // Сохраняем
                writer.writeStartElement("service");
                writer.writeAttribute("type", type);
                writer.writeEndElement(); // service
                sIt.next();
            }
            writer.writeEndElement(); // order
            oIt.next();
        }
        writer.writeEndElement(); // room
        it.next();
    }
    writer.writeEndElement(); // hotel
    writer.writeEndDocument();
    xml.close();
}
void MainWindow::updateCounters()
{
    ui->label_2->setText(QString("%1").arg(hotel.countRooms()));
    ui->label_3->setText(QString("%1").arg(hotel.countRooms(true)));
    ui->label_5->setText(QString("%1").arg(hotel.countRooms(false)));
}
void MainWindow::updateRoom(int number)
{
    for (int i = 0, c = ui->widget->layout()->count(); i < c; i++)
    {
        RoomListItem* item = (RoomListItem*)ui->widget->layout()->itemAt(i)->widget();
        if (item->room->getNumber() == number)
        {
            item->updateInfo();
            break;
        }
    }
}

void MainWindow::roomClicked()
{
    emit roomClicked((RoomListItem*)QObject::sender());
}
