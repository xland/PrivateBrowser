#include <QWidget>

class TitleBar : public QWidget
{
    Q_OBJECT
public:
    TitleBar(QWidget *parent = nullptr);
    ~TitleBar();
    QPoint getLogoRightBottom();
    // TitleBarLogo *titleBarLogo;

protected:
    void mouseMoveEvent(QMouseEvent *event);

private:
    // 自定义成员变量
};
