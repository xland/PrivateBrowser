
#include <QApplication>

#include "TitleBarWindowBtn.h"

TitleBarWindowBtn::TitleBarWindowBtn(QWidget *parent)
{
    setAttribute(Qt::WA_StyledBackground);
    setMinimumWidth(50);
    setMaximumWidth(50);
    setStyleSheet(R"(TitleBarWindowBtn{background-color: transparent;}
        TitleBarWindowBtn:hover {background-color: #BECCE3;}
    )");
}

TitleBarWindowBtn::~TitleBarWindowBtn()
{
}