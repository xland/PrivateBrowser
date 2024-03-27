#include "ControlBase.h"
#include <Windows.h>
#include <include/core/SkFontMetrics.h>
#include <include/core/SkFontTypes.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <filesystem>
#include <chrono>
#include <format>
#include <ctime>
#include "WindowMain.h"


ControlBase::ControlBase(WindowMain* root):root{root}
{
    root->ctrls.push_back(this);
}

ControlBase::~ControlBase()
{
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

float ControlBase::getTextVerticalVal(SkFont* font)
{
    SkFontMetrics metrics;
    font->getMetrics(&metrics);
    return (metrics.fDescent - metrics.fAscent) / 2 - metrics.fDescent;
}

std::wstring ControlBase::fileTimeToString(const std::filesystem::file_time_type& timePoint) {
    auto zone = std::chrono::current_zone();
    auto sysClock = std::chrono::clock_cast<std::chrono::system_clock>(timePoint);
    auto zTime = std::chrono::zoned_time(zone, sysClock);
    //auto now = std::chrono::zoned_time(zone, std::chrono::system_clock::now());
    //auto span = now.get_sys_time() - zTime.get_sys_time();
    //auto seconds = std::chrono::duration_cast<std::chrono::seconds>(span).count();
    auto str = std::format(L"{:%Y-%m-%d %H:%M:%S}", zTime);
    return str.substr(0, str.find_last_of(L"."));
}

void ControlBase::repaint()
{
    isDirty = true;
    InvalidateRect(root->hwnd, nullptr, false);
}

bool ControlBase::needPaint(SkCanvas* canvas,const SkColor& color)
{
    if (!isDirty) return false;
    SkPaint paint;
    paint.setColor(color);
    canvas->drawRect(rect, paint);
    isDirty = false;
    return true;
}
