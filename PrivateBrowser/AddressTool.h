#pragma once
#include "ControlBase.h"
class AddressTool : public ControlBase
{
public:
	AddressTool(ControlBase* parent) : ControlBase(parent) {};
private:
	void paint(SkCanvas* canvas) override;
	void resize(const int& w, const int& h) override;
	void mouseEnter(const int& x, const int& y) override;
	void mouseOut(const int& w, const int& h) override;
	void mouseDown(const int& w, const int& h) override;
	std::vector<const char*> codes{ (const char*)u8"\ue80b", (const char*)u8"\ue80c" ,
	(const char*)u8"\ue741",(const char*)u8"\ue630"  };
};

