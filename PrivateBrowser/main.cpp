#include "PrivateBrowser.h"

#include <QApplication>
#include <QNetworkProxyFactory>
#include <QWebEngineView>
#include "qguiapplication.h"

#include "Res.h"

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QNetworkProxyFactory::setUseSystemConfiguration(false);
    Res::init();
    QApplication a(argc, argv);
    PrivateBrowser w;
    w.show();
    return a.exec();
}