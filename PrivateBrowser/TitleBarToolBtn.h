#include <QWidget>
#include <qlabel.h>

class TitleBarToolBtn : public QLabel
{
    Q_OBJECT
public:
    TitleBarToolBtn(QWidget *parent = nullptr);
    ~TitleBarToolBtn();
};
