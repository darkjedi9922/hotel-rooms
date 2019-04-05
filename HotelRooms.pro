#-------------------------------------------------
#
# Project created by QtCreator 2017-11-04T15:59:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HotelRooms
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++0x

SOURCES += \
    main.cpp \
    classes/rooms/Room.cpp \
    classes/wviews/CityView.cpp \
    classes/Customer.cpp \
    classes/Date.cpp \
    classes/Hotel.cpp \
    classes/Order.cpp \
    classes/services/CleaningService.cpp \
    Window.cpp \
    MainWindow.cpp \
    RoomListItem.cpp \
    RoomWindow.cpp \
    OrderItem.cpp \
    CustomerItem.cpp \
    ServiceItem.cpp \
    OrderListWindow.cpp \
    MakeOrderWindow.cpp \
    CustomerEditForm.cpp \
    ServiceCheckBoxItem.cpp \
    classes/rooms/StandardRoom.cpp \
    classes/services/FoodDeliveryService.cpp \
    classes/services/WiFiService.cpp \
    classes/rooms/ApartmentRoom.cpp \
    classes/rooms/BusinessRoom.cpp \
    classes/rooms/DeLuxeRoom.cpp \
    classes/rooms/FamilyRoom.cpp \
    classes/rooms/PresidentRoom.cpp \
    classes/rooms/SuperiorRoom.cpp \
    classes/wviews/BeachView.cpp \
    classes/wviews/GardenView.cpp \

HEADERS  += \
    classes/rooms/Room.h \
    classes/services/CleaningService.h \
    classes/services/Service.h \
    classes/wviews/CityView.h \
    classes/wviews/ViewFromWindow.h \
    classes/Customer.h \
    classes/Date.h \
    classes/Hotel.h \
    classes/List.h \
    classes/Order.h \
    Window.h \
    MainWindow.h \
    RoomListItem.h \
    RoomWindow.h \
    OrderItem.h \
    CustomerItem.h \
    ServiceItem.h \
    OrderListWindow.h \
    MakeOrderWindow.h \
    CustomerEditForm.h \
    ServiceCheckBoxItem.h \
    classes/rooms/StandardRoom.h \
    classes/services/FoodDeliveryService.h \
    classes/services/WiFiService.h \
    classes/rooms/ApartmentRoom.h \
    classes/rooms/BusinessRoom.h \
    classes/rooms/DeLuxeRoom.h \
    classes/rooms/FamilyRoom.h \
    classes/rooms/PresidentRoom.h \
    classes/rooms/SuperiorRoom.h \
    classes/wviews/BeachView.h \
    classes/wviews/GardenView.h \

FORMS += \
    Window.ui \
    MainWindow.ui \
    RoomListItem.ui \
    RoomWindow.ui \
    OrderItem.ui \
    CustomerItem.ui \
    ServiceItem.ui \
    OrderListWindow.ui \
    MakeOrderWindow.ui \
    CustomerEditForm.ui \
    ServiceCheckBoxItem.ui
