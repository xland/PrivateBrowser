#pragma once
#include <include/core/SkRect.h>
#include <include/core/SkFont.h>
#include <include/core/SkCanvas.h>
#include <filesystem>
class WindowMain;

class ControlBase
{
public:
	ControlBase(ControlBase* parent=nullptr);
	~ControlBase();
	void repaint();
	void paintChildren(SkCanvas* canvas);
	void resizeChildren(const int& w, const int& h);
	void mouseMoveChildren(const int& x, const int& y);
	virtual void paint(SkCanvas* canvas) {};
	virtual void resize(const int& w, const int& h) {};
	virtual void mouseMove(const int& x, const int& y) {};
	virtual void mouseDown(const int& x, const int& y) {};
	virtual void mouseUp(const int& x, const int& y) {};
	virtual void mouseDrag(const int& x, const int& y) {};
	virtual void mouseWheel(const int&, const int&, const int&) {};
	virtual void timeout(const unsigned int& id) {};
	SkRect rect{SkRect::MakeEmpty()};
	bool isDirty{ true };
	bool isDel{ false };
	bool isHidden{ false };
	int hoverIndex{ -1 };
	std::vector<ControlBase*> ctrls;
	ControlBase* parent;
private:

};
