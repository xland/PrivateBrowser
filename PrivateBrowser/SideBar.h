#pragma once
#include "ControlBase.h"
class SideBar : public ControlBase
{
public:
	bool isDockRight{ true };
	float width{ 300.f };
private:
	void paint(SkCanvas* canvas) override;
	void resize(const int& w, const int& h) override;
};

