#include "TitleBar.h"
#include "TitleBarWindowBtns.h"
#include "AddressInput.h"

TitleBar::TitleBar()
{
	ctrls.push_back(new TitleBarWindowBtns(this));
	ctrls.push_back(new AddressInput(this));
}

TitleBar::~TitleBar()
{
}

void TitleBar::paint(SkCanvas* canvas)
{
	if (!isDirty) {
		return;
	}
	SkPaint paint;
	paint.setColor(0xFFD3E3FD);
	paint.setStyle(SkPaint::kFill_Style);
	canvas->drawRect(rect, paint);
	paint.setColor(0xFF0B57D0);
	canvas->drawLine(0.f, rect.fBottom-1, rect.fRight, rect.fBottom - 1, paint);
	paintChildren(canvas);
}
void TitleBar::resize(const int& w, const int& h)
{
	isDirty = true;
	rect.setLTRB(0, 0, w, 60.f);
	resizeChildren(w, h);
}

void TitleBar::mouseMove(const int& x, const int& y)
{
	mouseMoveChildren(x, y);
}
