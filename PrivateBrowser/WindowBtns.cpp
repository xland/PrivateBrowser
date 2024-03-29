#include "WindowBtns.h"
#include <Windows.h>
#include "App.h"


void WindowBtns::paint(SkCanvas* canvas)
{
	SkPaint paint;
	if (hoverIndex == 0) {
		paint.setColor(0xAAFFFFFF);
		canvas->drawRect(SkRect::MakeXYWH(rect.fLeft, rect.fTop, 66, rect.fBottom-1), paint);
	}
	else if (hoverIndex == 1) {
		paint.setColor(0xAAFFFFFF);
		canvas->drawRect(SkRect::MakeXYWH(rect.fLeft + 66, rect.fTop, 66, rect.fBottom - 1), paint);
	}
	else if (hoverIndex == 2) {
		paint.setColor(SK_ColorRED);
		canvas->drawRect(SkRect::MakeXYWH(rect.fLeft + 132, rect.fTop, 66, rect.fBottom - 1), paint);
	}
	auto font = App::getIconFont();
	font->setSize(24.f);
	auto iconCode = (const char*)u8"\ue6e8"; //最小化	
	paint.setColor(0xFF888888);
	auto left = rect.fLeft + 22.f;
	auto top = rect.fTop + 38.f;
	canvas->drawString(iconCode, left, top, *font, paint);
	auto isMaximized = IsZoomed(App::get()->windowMain->hwnd) != 0;
	iconCode = isMaximized ? (const char*)u8"\ue6e9" : (const char*)u8"\ue6e5"; //最大化
	canvas->drawString(iconCode, left + 66.f, top, *font, paint);
	iconCode = (const char*)u8"\ue6e7"; // 关闭
	if (hoverIndex == 2) {
		paint.setColor(SK_ColorWHITE);
	}
	canvas->drawString(iconCode, left + 132.f, top, *font, paint);

}

void WindowBtns::resize(const int& w, const int& h)
{
	isDirty = true;
	rect.setLTRB(w - 198.f, 0.f, (float)w, parent->rect.fBottom);
}

void WindowBtns::mouseEnter(const int& x, const int& y)
{
	int index = -1;
	if (x < rect.fLeft + 66) {
		index = 0;
	}
	else if (x < rect.fLeft + 132) {
		index = 1;
	}
	else {
		index = 2;
	}
	if (index != hoverIndex) {
		hoverIndex = index;
		repaint();
	}
}

void WindowBtns::mouseOut(const int& w, const int& h)
{
	hoverIndex = -1;
	repaint();
}

void WindowBtns::mouseDown(const int& w, const int& h)
{
	ReleaseCapture();
	auto win = App::get()->windowMain;
	if (hoverIndex == 0) {
		PostMessage(win->hwnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
		hoverIndex = -1;
		win->isMouseDown = false;
		repaint();
	}
	else if (hoverIndex == 1) {
		auto isMaximized = IsZoomed(win->hwnd) != 0;
		if (isMaximized) {
			PostMessage(win->hwnd, WM_SYSCOMMAND, SC_RESTORE, 0);
		}
		else {
			PostMessage(win->hwnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
		}
		win->isMouseDown = false;
		hoverIndex = -1;
		repaint();
	}
	else if (hoverIndex == 2) {
		PostMessage(win->hwnd, WM_CLOSE, 0, 0); //PostMessage异步，SendMessage同步
	}
	
}
