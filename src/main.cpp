#include "PrivateBrowser.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    PrivateBrowser w;
    w.show();
    return a.exec();
}