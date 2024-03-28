#pragma once
#include "ControlBase.h"
class TitleBar : public ControlBase
{
public:
	TitleBar();
	~TitleBar();
private:
	void paint(SkCanvas* canvas) override;
	void resize(const int& w, const int& h) override;
	void mouseMove(const int& x, const int& y) override;
};

