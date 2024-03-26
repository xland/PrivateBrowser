#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QApplication>
#include <qwindow.h>
#include <qwidget.h>


#include "TitleBar.h"
#include "TitleBarLogo.h"
#include "TitleBarToolBtn.h"
#include "TitleBarWindowBtn.h"

TitleBar::TitleBar(QWidget *parent)
{
    setAttribute(Qt::WA_StyledBackground);
    setStyleSheet(R"(TitleBar { background-color: #D3E3FD;})");
    this->setFixedHeight(40);
    auto layout = new QHBoxLayout(this);
    this->setLayout(layout);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    auto titleBarLogo = new TitleBarLogo(this);

    auto prevBtn = new TitleBarToolBtn(this);
    auto nextBtn = new TitleBarToolBtn(this);
    auto refreshBtn = new TitleBarToolBtn(this);
    auto homeBtn = new TitleBarToolBtn(this);

    auto addressBar = new QWidget(this);
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(1);
    addressBar->setSizePolicy(sizePolicy);

    auto minimizeBtn = new TitleBarWindowBtn(QChar(0xe6e8),false,this);
    connect(minimizeBtn, &TitleBarWindowBtn::clicked, [this]() {
        this->window()->showMinimized();
        });
    auto maximizeRestoreBtn = new TitleBarWindowBtn(QChar(0xe6e5), false,this);
    connect(maximizeRestoreBtn, &TitleBarWindowBtn::clicked, [this]() {
        this->window()->showMaximized();
        });
    auto closeBtn = new TitleBarWindowBtn(QChar(0xe6e7), true,this);
    connect(closeBtn, &TitleBarWindowBtn::clicked, [this]() {
        this->window()->close();
        });

    layout->addWidget(titleBarLogo);

    layout->addWidget(prevBtn);
    layout->addWidget(nextBtn);
    layout->addWidget(refreshBtn);
    layout->addWidget(homeBtn);

    layout->addWidget(addressBar);

    layout->addWidget(minimizeBtn);
    layout->addWidget(maximizeRestoreBtn);
    layout->addWidget(closeBtn);
}

TitleBar::~TitleBar()
{
}
QPoint TitleBar::getLogoRightBottom()
{
    return QPoint();
}
void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
}