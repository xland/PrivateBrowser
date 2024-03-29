#pragma once
#include "ControlBase.h"
class AddressInput : public ControlBase
{
public:
	AddressInput(ControlBase* parent);
private:
	void paint(SkCanvas* canvas) override;
	void resize(const int& w, const int& h) override;
	void mouseEnter(const int& w, const int& h) override;
	void mouseOut(const int& w, const int& h) override;
	void mouseDown(const int& w, const int& h) override;
};

