#include "Res.h"
#include <qfontdatabase.h>
#include <qlist.h>
Res* res;
Res::Res()
{
}

Res::~Res()
{
}

void Res::init()
{
	res = new Res();
}

QFont* Res::getIcon(int size)
{
    if (res->iconFont == NULL) {
        int fontId = QFontDatabase::addApplicationFont(":/font/res/iconfont.ttf");
        QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
        res->iconFont = new QFont(fontName);
    }
    res->iconFont->setPixelSize(size);
    return res->iconFont;
}
