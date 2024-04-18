#include "AddressTool.h"
#include "App.h"

void AddressTool::paint(SkCanvas* canvas)
{
	SkPaint paint;
	float start{ rect.fLeft + 3.f };
	float top{ rect.fTop + 30.f };
	auto font = App::getIconFont();
	font->setSize(26.f);
	for (size_t i = 0; i < codes.size(); i++)
	{
		if (hoverIndex == i) {
			paint.setColor(0x18000000);  //0xFFA8C7FA
			auto r = SkRect::MakeXYWH(rect.fLeft + hoverIndex * 40.f, rect.fTop + 16.f, 34.f, 30.f);
			canvas->drawRoundRect(r, 6.f, 6.f, paint);
			paint.setColor(0xFF222222);
		}
		else {
			paint.setColor(0xFF888888);
		}
		canvas->drawString(codes[i], start + i * 40.f, top, *font, paint);
	}
}

void AddressTool::resize(const int& w, const int& h)
{
	isDirty = true;
	rect.setLTRB(parent->rect.fRight-160, parent->rect.fTop, parent->rect.fRight, parent->rect.fBottom);
}

void AddressTool::mouseEnter(const int& x, const int& y)
{
	//int index = -1;
	//if (x < rect.fLeft + 66) {
	//	index = 0;
	//}
	//else if (x < rect.fLeft + 132) {
	//	index = 1;
	//}
	//else {
	//	index = 2;
	//}
	//if (index != hoverIndex) {
	//	hoverIndex = index;
	//	repaint();
	//}
}

void AddressTool::mouseOut(const int& w, const int& h)
{
}

void AddressTool::mouseDown(const int& w, const int& h)
{
}
