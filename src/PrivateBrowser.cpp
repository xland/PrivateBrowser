#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>
#include <QTextEdit>

#include "PrivateBrowser.h"
#include "TitleBar.h"
#include "LeftBar.h"

PrivateBrowser::PrivateBrowser(QWidget *parent)
    : QMainWindow(parent)
{
    setMinimumSize(1200, 800);
    auto container = new QWidget(this);
    setCentralWidget(container);

    auto splitter = new QSplitter(Qt::Horizontal, container);
    auto leftBar = new LeftBar(splitter);
    splitter->addWidget(leftBar);
    auto widget = new QWidget(splitter);
    splitter->addWidget(widget);
    splitter->setSizes({100, width() - 100});
    // setWindowFlags(Qt::FramelessWindowHint);

    auto winLayout = new QVBoxLayout(container);
    container->setLayout(winLayout);
    winLayout->addWidget(new TitleBar(container));
    winLayout->setContentsMargins(0, 0, 0, 0);
    winLayout->setSpacing(0);

    winLayout->addWidget(splitter);

    auto vboxLayout = new QVBoxLayout(splitter);
    vboxLayout->setContentsMargins(0, 0, 0, 0);
    vboxLayout->setSpacing(0);

    auto textRight1 = new QTextEdit("右侧1");
    textRight1->setFixedHeight(30);
    auto textRight2 = new QTextEdit("右侧2");
    vboxLayout->addWidget(textRight1);
    vboxLayout->addWidget(textRight2);
    widget->setLayout(vboxLayout);
    // setCentralWidget(winLayout);
}

PrivateBrowser::~PrivateBrowser()
{
}