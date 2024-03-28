#include "AddressInput.h"

void AddressInput::paint(SkCanvas* canvas)
{
	if (!isDirty) {
		return;
	}
	SkPaint paint;
	paint.setAntiAlias(true);
	paint.setStroke(true);
	paint.setStrokeWidth(1.5f);
	paint.setColor(0xFF0B57D0);
	canvas->drawRoundRect(rect, 8.f, 8.f, paint);
	paint.setColor(0xFFECEFF7);
	paint.setStroke(false);
	canvas->drawRoundRect(rect, 8.f, 8.f, paint);
}

void AddressInput::resize(const int& w, const int& h)
{
	isDirty = true;
	rect.setLTRB(20.f, 10.f, w-320.f, 50.f);
}

void AddressInput::mouseMove(const int& x, const int& y)
{
}
