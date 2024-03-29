#pragma once
#include "ControlBase.h"
class TitleBarWindowBtns : public ControlBase
{
public:
	TitleBarWindowBtns(ControlBase* parent) : ControlBase(parent) {};
private:
	void paint(SkCanvas* canvas) override;
	void resize(const int& w, const int& h) override;
	void mouseEnter(const int& x, const int& y) override;
	void mouseOut(const int& w, const int& h) override;
};

