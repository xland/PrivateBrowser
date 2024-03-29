#pragma once
#include "ControlBase.h"
#include <Windows.h>
class TitleBar : public ControlBase
{
public:
	TitleBar();
	~TitleBar();
private:
	void paint(SkCanvas* canvas) override;
	void resize(const int& w, const int& h) override;
	void mouseDown(const int& w, const int& h) override;
	void mouseDrag(const int& w, const int& h) override;
	void mouseUp(const int& w, const int& h) override;
	bool isDragging{ false };
	POINT startPos;
};

