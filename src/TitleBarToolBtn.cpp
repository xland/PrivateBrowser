#include "TitleBarToolBtn.h"

TitleBarToolBtn::TitleBarToolBtn(QWidget *parent)
{
    QString styleSheet = R"(TitleBarToolBtn:{margin-left:8px;margin-right:8px;background-color: #4CAF50;})";
    setStyleSheet(styleSheet);
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setSizePolicy(sizePolicy);

    setFixedSize(36, 30);
}

TitleBarToolBtn::~TitleBarToolBtn()
{
}