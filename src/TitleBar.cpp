#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QApplication>

#include "TitleBar.h"
#include "TitleBarToolBtn.h"

TitleBar::TitleBar(QWidget *parent)
{
    setObjectName("TitleBar");
    qApp->setStyleSheet(R"(#TitleBar {
        background-color: #987654;
        })");
    this->setFixedHeight(40);
    auto layout = new QHBoxLayout(this);
    this->setLayout(layout);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    auto label = new QLabel(this);
    label->setText("私人浏览器");

    auto prevBtn = new TitleBarToolBtn(this);
    auto nextBtn = new TitleBarToolBtn(this);
    auto refreshBtn = new TitleBarToolBtn(this);
    auto homeBtn = new TitleBarToolBtn(this);

    auto addressBar = new QWidget(this);
    // QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    // sizePolicy.setHorizontalStretch(1);
    // addressBar->setSizePolicy(sizePolicy);

    auto minimizeBtn = new QPushButton("minimize", this);
    auto maximizeRestoreBtn = new QPushButton("maximize", this);
    auto closeBtn = new QPushButton("close", this);
    minimizeBtn->setFixedSize(60, 40);
    maximizeRestoreBtn->setFixedSize(60, 40);
    closeBtn->setFixedSize(60, 40);
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    minimizeBtn->setSizePolicy(sizePolicy);
    maximizeRestoreBtn->setSizePolicy(sizePolicy);
    closeBtn->setSizePolicy(sizePolicy);

    layout->addWidget(label);

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