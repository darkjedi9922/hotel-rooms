#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "ui_MainWindow.h"
#include "RoomListItem.h"
#include "classes/Hotel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void loadData();
    void saveData();
    void updateCounters();
    void updateRoom(int number);

    Ui::MainWindow *ui;
    Hotel hotel;

signals:
    void roomClicked(RoomListItem*);

private slots:
    void roomClicked();
};

#endif // MAINWINDOW_H
