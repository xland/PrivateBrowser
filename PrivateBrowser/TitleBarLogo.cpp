#include "TitleBarLogo.h"
#include <QWindow>
#include <QScreen>
#include <QLabel>
#include <QHBoxLayout>
#include <QFontDatabase>

#include "Res.h"

TitleBarLogo::TitleBarLogo(QWidget *parent)
{
    setAttribute(Qt::WA_StyledBackground);
    setStyleSheet(R"(TitleBarLogo { background-color: #639584;})");
    setMinimumWidth(130);
    setMaximumWidth(130);
    auto l = new QLabel("allen", this);

    l->setFont(*Res::getIcon());
    l->setText(QChar(0xe6e7));

    auto layout = new QHBoxLayout(this);
    setLayout(layout);
    layout->addWidget(l);
}

TitleBarLogo::~TitleBarLogo()
{
}