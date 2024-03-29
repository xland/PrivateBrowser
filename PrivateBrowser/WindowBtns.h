#pragma once
#include "ControlBase.h"
class WindowBtns : public ControlBase
{
public:
	WindowBtns(ControlBase* parent) : ControlBase(parent) {};
private:
	void paint(SkCanvas* canvas) override;
	void resize(const int& w, const int& h) override;
	void mouseEnter(const int& x, const int& y) override;
	void mouseOut(const int& w, const int& h) override;
};

