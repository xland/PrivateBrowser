#include "TitleBarToolBtn.h"
#include "Res.h"

TitleBarToolBtn::TitleBarToolBtn(QWidget *parent)
{
    setFont(*Res::getIcon());
    setAutoFillBackground(true);
    setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    setCursor(Qt::PointingHandCursor);
    setAttribute(Qt::WA_StyledBackground);
    setStyleSheet(R"(TitleBarToolBtn {margin-left:4px;margin-right:4px;background-color: #A8C7FA;border-radius:8px;color:#4E6EF2;}
    TitleBarToolBtn:hover {background-color: #97B6E9;color:#FFF;}
    )");
    setMinimumSize(28, 20);
    setMaximumSize(28, 20);
}

TitleBarToolBtn::~TitleBarToolBtn()
{
}