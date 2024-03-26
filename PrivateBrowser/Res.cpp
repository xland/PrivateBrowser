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

QFont* Res::getIcon()
{
    if (res->iconFont == NULL) {
        int fontId = QFontDatabase::addApplicationFont(":/font/res/iconfont.ttf");
        QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
        res->iconFont = new QFont(fontName,13);
    }
    return res->iconFont;
}
