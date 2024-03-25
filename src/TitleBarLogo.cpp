#include "TitleBarLogo.h"
#include <QWindow>
#include <QScreen>
#include <QLabel>
#include <QHBoxLayout>
#include <QFontDatabase>

TitleBarLogo::TitleBarLogo(QWidget *parent)
{
    setAttribute(Qt::WA_StyledBackground);
    setStyleSheet(R"(TitleBarLogo { background-color: #639584;})");
    setMinimumWidth(130);
    setMaximumWidth(130);
    auto l = new QLabel("allen", this);

    int fontId = QFontDatabase::addApplicationFont(":/font/iconfont.ttf");
    QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
    auto iconFont = new QFont(fontName);
    iconFont->setPixelSize(10);
    l->setFont(*iconFont);
    l->setText(QChar(0xe6e7));

    auto layout = new QHBoxLayout(this);
    setLayout(layout);
    layout->addWidget(l);
}

TitleBarLogo::~TitleBarLogo()
{
}