#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>
#include <QTextEdit>

#include "PrivateBrowser.h"

PrivateBrowser::PrivateBrowser(QWidget *parent)
    : QMainWindow(parent)
{
    auto splitter = new QSplitter(Qt::Horizontal, this);
    auto textLeft = new QTextEdit("左侧", splitter);
    auto widget = new QWidget(splitter);
    auto vboxLayout = new QVBoxLayout(splitter);

    auto textRight1 = new QTextEdit("右侧1");
    auto textRight2 = new QTextEdit("右侧2");
    vboxLayout->addWidget(textRight1);
    vboxLayout->addWidget(textRight2);

    widget->setLayout(vboxLayout);
    setCentralWidget(splitter);
}

PrivateBrowser::~PrivateBrowser()
{
}