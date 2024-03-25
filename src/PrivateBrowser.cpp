#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>
#include <QTextEdit>
#include <QGraphicsDropShadowEffect>
#include <QWebEngineView>
#include <QObject>

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

    auto winLayout = new QVBoxLayout(container);
    winLayout->setContentsMargins(10, 10, 10, 10);
    winLayout->setSpacing(0);
    container->setLayout(winLayout);

    winLayout->addWidget(new TitleBar(container));
    auto splitter = new QSplitter(Qt::Horizontal, container);
    splitter->setSizes({100, width() - 100});
    winLayout->addWidget(splitter);

    // splitter->setObjectName("splitter");
    // splitter->setStyleSheet(R"(#splitter{border:0.5px solid #333;border-top:none;})");
    auto leftBar = new LeftBar(splitter);
    splitter->addWidget(leftBar);
    {
        auto *webView = new QWebEngineView(splitter);
        webView->setBackgroundRole(QPalette::ColorRole::Dark);
        // webView->setUrl(QUrl("https://www.baidu.com"));
        webView->setHtml("<html><head></head><body>测试abc</body></html>");
        // 连接QWebEnginePage的loadFinished信号到自定义槽函数
        connect(webView, &QWebEngineView::loadFinished, [this](bool ok)
                {
                auto a = 1;
                this->clearFocus(); });
        splitter->addWidget(webView);
    }
    // auto browserContent = new QWidget(this);
    // browserContent->setStyleSheet(R"(background:#687;)");
}

PrivateBrowser::~PrivateBrowser()
{
}