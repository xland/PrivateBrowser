#include "TitleBar.h"
#include "WindowBtns.h"
#include "AddressInput.h"
#include "Windows.h"
#include "App.h"

TitleBar::TitleBar()
{
	ctrls.push_back(new AddressInput(this));
	ctrls.push_back(new WindowBtns(this));
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
	paint.setColor(0xFFbae0ff);
	paint.setStyle(SkPaint::kFill_Style);
	canvas->drawRect(rect, paint);
	paint.setColor(0xFFBBBBBB);
	canvas->drawLine(0.f, rect.fBottom-1, rect.fRight, rect.fBottom - 1, paint);
	paintChildren(canvas);
}
void TitleBar::resize(const int& w, const int& h)
{
	isDirty = true;
	rect.setLTRB(0, 0, w, 60.f);
	resizeChildren(w, h);
}

void TitleBar::mouseDown(const int& w, const int& h)
{
	isDragging = true;
	GetCursorPos(&startPos);
	ScreenToClient(App::get()->windowMain->hwnd, &startPos);
	SetCapture(App::get()->windowMain->hwnd);
}

void TitleBar::mouseDrag(const int& w, const int& h)
{
	if (!isDragging) return;
	POINT point;
	auto hwnd = App::get()->windowMain->hwnd;
	GetCursorPos(&point);
	ScreenToClient(hwnd, &point);
	RECT windowRect;
	GetWindowRect(hwnd, &windowRect);
	int dx = windowRect.left + point.x - startPos.x;
	int dy = windowRect.top + point.y - startPos.y;
	SetWindowPos(hwnd, nullptr, dx, dy, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void TitleBar::mouseUp(const int& w, const int& h)
{
	isDragging = false;
	ReleaseCapture();
}
