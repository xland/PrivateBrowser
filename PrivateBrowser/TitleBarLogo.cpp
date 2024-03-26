#include "TitleBarLogo.h"
#include <QWindow>
#include <QScreen>
#include <QLabel>
#include <QHBoxLayout>
#include <QFontDatabase>

#include "Res.h"

TitleBarLogo::TitleBarLogo(QWidget *parent)
{
    setMinimumWidth(160);
    setMaximumWidth(160);
    auto layout = new QHBoxLayout(this);
    layout->setContentsMargins(10, 0, 60, 0);
    setLayout(layout);

    auto logo = new QLabel(this);
    logo->setFont(*Res::getIcon(21));
    logo->setText(QChar(0xe644));
    QPalette pa = logo->palette();
    pa.setColor(QPalette::ColorRole::WindowText, QColor("#4E6EF2"));
    logo->setPalette(pa);
    layout->addWidget(logo);

    auto title = new QLabel(this);
    title->setText("我的浏览器");
    layout->addWidget(title);
}

TitleBarLogo::~TitleBarLogo()
{
}