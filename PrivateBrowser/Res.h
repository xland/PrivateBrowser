#pragma once
#include <qfont.h>

class Res
{
public:
	Res();
	~Res();
	static void init();
	static QFont* getIcon();
private:
	QFont* iconFont {nullptr};
};

