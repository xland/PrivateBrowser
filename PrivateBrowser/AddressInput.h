#pragma once
#include "ControlBase.h"
class AddressInput : public ControlBase
{
public:
	AddressInput(ControlBase* parent) : ControlBase(parent) {};
private:
	void paint(SkCanvas* canvas) override;
	void resize(const int& w, const int& h) override;
	void mouseMove(const int& x, const int& y) override;
};

