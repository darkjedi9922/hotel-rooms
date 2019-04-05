#include <QDebug>
#include <QApplication>
#include "Window.h"
#include <string.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Window window;
    window.show();

    return app.exec();
}
