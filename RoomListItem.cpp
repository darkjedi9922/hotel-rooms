#include "RoomListItem.h"

RoomListItem::RoomListItem(Room *room, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoomListItem)
{
    ui->setupUi(this);
    setAutoFillBackground(true);

    this->room = room;
    updateInfo();
}
RoomListItem::~RoomListItem()
{
    delete ui;
}
void RoomListItem::updateInfo()
{
    ui->label_2->setText(QString("%1").arg(room->getNumber()));
    ui->label_4->setText(QString::fromStdString(room->getInfo()));
    ui->label_8->setText(QString::fromStdString(room->getViewFromWindow()->getInfo()));
    ui->label_12->setText(QString("%1").arg(room->getMaxCustomersCount()));
    QPalette palette = ui->label_10->palette();
    palette.setBrush(QPalette::Foreground, (room->isBusy() ? QColor(Qt::red) : QColor(Qt::darkGreen)));
    ui->label_10->setPalette(palette);
    ui->label_10->setText(room->isBusy() ? "Занято" : "Свободно");
    ui->label_6->setText(QString("$%1").arg(room->getDollarPrice()));
}

void RoomListItem::enterEvent(QEvent *)
{
    QPalette pal;
    pal.setBrush(QPalette::Background, QBrush(QColor("#e1e1e1")));
    setPalette(pal);
}
void RoomListItem::leaveEvent(QEvent *)
{
    QPalette pal;
    pal.setBrush(QPalette::Background, QBrush(QColor(Qt::transparent)));
    setPalette(pal);
}
void RoomListItem::mouseReleaseEvent(QMouseEvent *)
{
    emit mouseReleased();
}
