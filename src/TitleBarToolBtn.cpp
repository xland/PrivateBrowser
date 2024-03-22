#include "TitleBarToolBtn.h"

TitleBarToolBtn::TitleBarToolBtn(QWidget *parent)
{
    setAttribute(Qt::WA_StyledBackground);
    setStyleSheet(R"(TitleBarToolBtn {margin-left:4px;margin-right:4px;background-color: #4CAF50;border-radius:8px;}
    TitleBarToolBtn:hover {background-color: #A8C7FA;}
    )");
    setMinimumSize(30, 22);
    setMaximumSize(30, 22);
}

TitleBarToolBtn::~TitleBarToolBtn()
{
}