#include <qwidget.h>
#include <QLabel>
class TitleBarWindowBtn : public QLabel
{
    Q_OBJECT
public:
    TitleBarWindowBtn(QChar&& icon, bool isClose = false,QWidget *parent = nullptr);
    ~TitleBarWindowBtn();
signals:
    void clicked();
protected:
    bool eventFilter(QObject* obj, QEvent* event);
    void mousePressEvent(QMouseEvent* event) override;
private:
    bool isClose;
};
