#include "SideBar.h"

void SideBar::paint(SkCanvas* canvas)
{
	SkPaint paint;
	paint.setColor(0xFFe6f4ff);
	canvas->drawRect(rect, paint);
	//paint.setColor(0xFF1677ff);
	//paint.setStrokeWidth(4.f);
	//canvas->drawLine(rect.fLeft+2, rect.fTop, rect.fLeft+2, rect.fBottom, paint);
}

void SideBar::resize(const int& w, const int& h)
{
	if (isDockRight) {
		isDirty = true;
		rect.setLTRB(w - width, 60.f, w, h);
		resizeChildren(w, h);
	}
	else {
		rect.setLTRB(0, 60.f, width, h);
	}
}
