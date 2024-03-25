#pragma once
#include <QMainWindow>

class PrivateBrowser : public QMainWindow
{
    Q_OBJECT

public:
    PrivateBrowser(QWidget *parent = nullptr);
    ~PrivateBrowser();

protected:
    bool nativeEvent(const QByteArray &eventType, void *message, qintptr *result) override;
    void showEvent(QShowEvent *event) override;

private:
    qreal dpr;
    int ncTest(const int &x, const int &y);
};