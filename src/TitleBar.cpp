#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QApplication>

#include "TitleBar.h"
#include "TitleBarToolBtn.h"
#include "TitleBarLogo.h"
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

    auto minimizeBtn = new TitleBarWindowBtn(this);
    auto maximizeRestoreBtn = new TitleBarWindowBtn(this);
    auto closeBtn = new TitleBarWindowBtn(this);

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
void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
}