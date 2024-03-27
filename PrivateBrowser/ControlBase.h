#pragma once
#include <include/core/SkRect.h>
#include <include/core/SkFont.h>
#include <include/core/SkCanvas.h>
#include <filesystem>
class WindowMain;

class ControlBase
{
public:
	ControlBase(WindowMain* root);
	~ControlBase();
	//SkPoint getStartPosOfIconAtCenterOfRect(const char* text,SkRect& rect,SkFont* font);
	//SkPoint getStartPosOfIconAtCenterOfRect(std::wstring& str,SkRect& rect, SkFont* font);
	float getTextVerticalVal(SkFont* font);
	std::wstring fileTimeToString(const std::filesystem::file_time_type& timePoint);
	void repaint();
	bool needPaint(SkCanvas* canvas, const SkColor& color = 0xFFFFFFFF);
	virtual void paint(SkCanvas* canvas) {};
	virtual void resize(const int& w, const int& h) {};
	virtual void mouseMove(const int& x, const int& y) {};
	virtual void mouseDown(const int& x, const int& y) {};
	virtual void mouseUp(const int& x, const int& y) {};
	virtual void mouseDrag(const int& x, const int& y) {};
	virtual void mouseWheel(const int&, const int&, const int&) {};
	virtual void timeout(const unsigned int& id) {};
	SkRect rect;
	WindowMain* root;
	bool isDirty{ true };
	bool isDel{ false };
private:

};
