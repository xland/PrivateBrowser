#include "PrivateBrowser.h"

#include <QApplication>
#include <QNetworkProxyFactory>
#include <QWebEngineView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QNetworkProxyFactory::setUseSystemConfiguration(false);
    PrivateBrowser w;
    w.show();
    return a.exec();
}