#include "AddressInput.h"

void AddressInput::paint(SkCanvas* canvas)
{
	if (!isDirty) {
		return;
	}
	SkPaint paint;
	paint.setColor(0xFFFFFFFF);
	paint.setStroke(false);
	canvas->drawRoundRect(rect, 8.f, 8.f, paint);
	paint.setAntiAlias(true);
	paint.setStroke(true);
	paint.setStrokeWidth(1.f);
	paint.setColor(0xFF69b1ff); //0xFFD3E3FD
	canvas->drawRoundRect(rect, 8.f, 8.f, paint);
}

void AddressInput::resize(const int& w, const int& h)
{
	isDirty = true;
	rect.setLTRB(20.f, 10.f, w-320.f, 50.f);
}
