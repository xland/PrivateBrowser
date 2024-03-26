#include <qwidget.h>
#include <QLabel>
class TitleBarWindowBtn : public QLabel
{
    Q_OBJECT
public:
    TitleBarWindowBtn(QChar&& icon, bool isClose = false,QWidget *parent = nullptr);
    ~TitleBarWindowBtn();
protected:
    bool eventFilter(QObject* obj, QEvent* event);
private:
    bool isClose;
};
