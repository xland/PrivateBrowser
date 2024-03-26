#pragma once
#include <qfont.h>

class Res
{
public:
	Res();
	~Res();
	static void init();
	static QFont* getIcon(int size=16);
private:
	QFont* iconFont {nullptr};
};

