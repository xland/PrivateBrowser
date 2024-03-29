#include "ControlBase.h"
#include <Windows.h>
#include <include/core/SkFontMetrics.h>
#include <include/core/SkFontTypes.h>
#include "WindowMain.h"
#include "App.h"


ControlBase::ControlBase(ControlBase* parent):
    rect{SkRect::MakeEmpty()},parent{ parent }
{
}

ControlBase::~ControlBase()
{
    for (auto ctrl: ctrls)
    {
        delete ctrl;
    }
}

//SkPoint ControlBase::getStartPosOfIconAtCenterOfRect(const char* text, SkRect& rect, SkFont* font)
//{
//    SkFontMetrics metrics;
//    font->getMetrics(&metrics);
//    SkRect textBounds;
//    font->measureText(text, 4, SkTextEncoding::kUTF8, &textBounds);
//    SkScalar x = rect.centerX() - textBounds.width() / 2 - textBounds.fLeft/2;
//    SkScalar y = rect.centerY() + (metrics.fDescent - metrics.fAscent) / 2 - metrics.fDescent;
//    return SkPoint(x, y);
//}
//
//SkPoint ControlBase::getStartPosOfIconAtCenterOfRect(std::wstring& str, SkRect& rect, SkFont* font)
//{
//    auto textLength = wcslen(str.data()) * 2;
//    SkFontMetrics metrics;
//    font->getMetrics(&metrics);
//    SkRect textBounds;
//    font->measureText(str.data(), textLength, SkTextEncoding::kUTF16, &textBounds);
//    SkScalar x = rect.centerX() - textBounds.width() / 2;
//    SkScalar y = rect.centerY() + (metrics.fDescent - metrics.fAscent) / 2 - metrics.fDescent;
//    return SkPoint(x, y);
//}

void ControlBase::repaint()
{
    isDirty = true;
    //RECT r{ .left{(LONG)rect.fLeft},.top{(LONG)rect.fTop},.right{(LONG)rect.fRight},.bottom{(LONG)rect.fBottom} };
    //InvalidateRect(App::get()->windowMain->hwnd, &r, false);
    InvalidateRect(App::get()->windowMain->hwnd, nullptr, false);
}

void ControlBase::paintChildren(SkCanvas* c)
{
    for (size_t i = 0; i < ctrls.size(); i++)
    {
        ctrls[i]->paint(c);
    }
}

void ControlBase::resizeChildren(const int& w, const int& h)
{
    for (size_t i = 0; i < ctrls.size(); i++)
    {
        ctrls[i]->resize(w,h);
    }
}

ControlBase* ControlBase::contain(const int& x, const int& y)
{
    if (rect.contains(x, y)) {
        for (size_t i = 0; i < ctrls.size(); i++)
        {
            auto ctrl = ctrls[i]->contain(x, y);
            if (ctrl) {
                return ctrl;
            }
        }
        return this;
    }
    return nullptr;
}
