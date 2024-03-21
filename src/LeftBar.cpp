#include <QLabel>
#include <QVBoxLayout>

#include "LeftBar.h"

LeftBar::LeftBar(QWidget *parent)
{
    setMinimumWidth(160);
    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    auto btn = new QLabel("allen", this);
    layout->addWidget(btn);
    setLayout(layout);
    setStyleSheet("background-color: #fff;");
}

LeftBar::~LeftBar()
{
}