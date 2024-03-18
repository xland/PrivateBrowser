#include <QHBoxLayout>
#include <QSplitter>
#include <QTextEdit>

#include "PrivateBrowser.h"

PrivateBrowser::PrivateBrowser(QWidget *parent)
    : QMainWindow(parent)
{
    auto splitter = new QSplitter(Qt::Horizontal, this);
    auto textLeft = new QTextEdit("左侧", splitter);
    auto textRight = new QTextEdit("右侧", splitter);
    splitter->setStretchFactor(1, 1);
    setCentralWidget(splitter);
}

PrivateBrowser::~PrivateBrowser()
{
}