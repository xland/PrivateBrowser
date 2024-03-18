#pragma once
#include <QMainWindow>

class PrivateBrowser : public QMainWindow {
    Q_OBJECT

public:
    PrivateBrowser(QWidget* parent = nullptr);
    ~PrivateBrowser();
};