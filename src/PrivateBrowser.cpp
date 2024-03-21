#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>
#include <QTextEdit>
#include <QGraphicsDropShadowEffect>
#include <QWebEngineView>

#include "PrivateBrowser.h"
#include "TitleBar.h"
#include "LeftBar.h"

PrivateBrowser::PrivateBrowser(QWidget *parent)
    : QMainWindow(parent)
{
    qDebug() << "allen";
    setWindowFlags(Qt::FramelessWindowHint);
    auto shadowEffect = new QGraphicsDropShadowEffect();
    shadowEffect->setBlurRadius(20);
    shadowEffect->setColor(Qt::gray);
    shadowEffect->setOffset(0, 0);
    setGraphicsEffect(shadowEffect);
    setAttribute(Qt::WA_TranslucentBackground, true);

    setMinimumSize(1200, 800);
    auto container = new QWidget(this);
    setCentralWidget(container);

    auto splitter = new QSplitter(Qt::Horizontal, container);
    // splitter->setObjectName("splitter");
    // splitter->setStyleSheet(R"(#splitter{border:0.5px solid #333;border-top:none;})");
    auto leftBar = new LeftBar(splitter);
    splitter->addWidget(leftBar);
    // auto *webView = new QWebEngineView(this);
    // webView->setUrl(QUrl("https://www.baidu.com"));
    // webView->show();
    // webView->resize(1024, 800);
    auto browserContent = new QWidget(this);
    browserContent->setStyleSheet(R"(background:#fff;)");
    splitter->addWidget(browserContent);
    splitter->setSizes({100, width() - 100});

    auto winLayout = new QVBoxLayout(container);
    container->setLayout(winLayout);
    winLayout->addWidget(new TitleBar(container));
    winLayout->setContentsMargins(10, 10, 10, 10);
    winLayout->setSpacing(0);
    winLayout->addWidget(splitter);
}

PrivateBrowser::~PrivateBrowser()
{
}