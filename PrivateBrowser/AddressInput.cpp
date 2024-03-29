#include "AddressInput.h"
#include <Windows.h>
#include "AddressTool.h"


AddressInput::AddressInput(ControlBase* parent) : ControlBase(parent) {
	ctrls.push_back(new AddressTool(this));
};

void AddressInput::paint(SkCanvas* canvas)
{
	if (!isDirty) {
		return;
	}
	SkPaint paint;	
	if (hoverIndex == 99) {
		paint.setColor(0xFFffffff);
	}
	else if (hoverIndex == 0) {
		paint.setColor(0xFFf0f5ff);
	}
	else {
		paint.setColor(0xFFe6f4ff);
	}
	canvas->drawRoundRect(rect, 8.f, 8.f, paint);
	paint.setAntiAlias(true);
	paint.setStroke(true);
	paint.setStrokeWidth(1.f);
	paint.setColor(0xFF69b1ff); //0xFFD3E3FD
	canvas->drawRoundRect(rect, 8.f, 8.f, paint);
	paintChildren(canvas);
}

void AddressInput::resize(const int& w, const int& h)
{
	isDirty = true;
	rect.setLTRB(30.f, 10.f, w-330.f, 50.f);
	resizeChildren(w, h);
}

void AddressInput::mouseEnter(const int& w, const int& h)
{
	if (hoverIndex == 99) {
		return;
	}
	auto index = -1;
	if (1) {
		index = 0;
	}
	if (hoverIndex != index) {
		if (index == 0) {
			SetCursor(LoadCursor(nullptr, IDC_IBEAM));
		}
		hoverIndex = index;
		repaint();
	}
}

void AddressInput::mouseOut(const int& w, const int& h)
{
	if (hoverIndex == 99) {
		return;
	}
	if (hoverIndex != -1) {
		SetCursor(LoadCursor(nullptr, IDC_ARROW));
		hoverIndex = -1;
		repaint();
	}
}

void AddressInput::mouseDown(const int& w, const int& h)
{
	hoverIndex = 99;
	repaint();
}
