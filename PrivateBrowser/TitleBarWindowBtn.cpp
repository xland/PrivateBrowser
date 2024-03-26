#include <QApplication>
#include "qpalette.h"

#include "Res.h"
#include "TitleBarWindowBtn.h"

TitleBarWindowBtn::TitleBarWindowBtn(QChar&& icon, bool isClose, QWidget *parent) :isClose{ isClose }
{
    installEventFilter(this);
    setAutoFillBackground(true);
    setMinimumWidth(50);
    setMaximumWidth(50);
    setFont(*Res::getIcon());
    setText(icon);
    setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    QPalette pa = palette();
    pa.setColor(QPalette::ColorRole::Window, Qt::transparent);
    pa.setColor(QPalette::ColorRole::WindowText, QColor("#666"));
    setPalette(pa);
    setCursor(Qt::PointingHandCursor);
}

TitleBarWindowBtn::~TitleBarWindowBtn()
{
}

bool TitleBarWindowBtn::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::Enter) {
        setMouseTracking(true);
        auto bg = isClose ? QColor("#E61123") : QColor("#BECCE3");
        auto fore = isClose ? QColor("#FFF") : QColor("#666");
        QPalette palette = this->palette();
        palette.setColor(QPalette::ColorRole::Window, bg);
        palette.setColor(QPalette::ColorRole::WindowText, fore);
        this->setPalette(palette);
        return true;
    }
    else if (event->type() == QEvent::Leave) {
        setMouseTracking(false);
        QPalette palette = this->palette();
        palette.setColor(QPalette::ColorRole::Window, Qt::transparent);
        palette.setColor(QPalette::ColorRole::WindowText, QColor("#666"));
        this->setPalette(palette);
        return true;
    }
    return QWidget::eventFilter(obj, event);
}
