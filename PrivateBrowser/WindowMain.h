#pragma once
#include <Windows.h>
#include <string>
#include <format>
#include <wrl.h>
#include <wil/com.h>
#include <WebView2.h>
#include <include/core/SkSurface.h>
#include <include/core/SkCanvas.h>
#include <src/base/SkAutoMalloc.h>

#include "Page.h"
#include "ControlBase.h"

class WindowMain
{
public:
	WindowMain(const HINSTANCE& hInstance);
	~WindowMain();
	void show();
	void initWindow(const HINSTANCE& hInstance);
	bool CreatePageController();
	ControlBase* hoverCtrl;
	std::unique_ptr<SkCanvas> canvas;
	std::vector<ControlBase*> ctrls;
	SkAutoMalloc surfaceMemory;
	HWND hwnd;
	bool isMouseDown{ false };
	wil::com_ptr<ICoreWebView2Controller> controller;
	wil::com_ptr<ICoreWebView2Controller> controller2;
protected:
	void paintWindow();
	void onSize(const int& w, const int& h);
	void mouseMove(const int& x, const int& y);
private:
	static LRESULT CALLBACK RouteWindowMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	HRESULT pageCtrlCallBack(HRESULT result, ICoreWebView2Controller* controller);
	LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	int nctest(const int& x, const int& y);
	bool isTrackMouseEvent{ false };
	long w{ 1200 }, h{800};
	int x, y;
	void* pixelData;
	unsigned long pixelDataSize;
	HBITMAP bitmap;
	HDC compatibleDC = NULL;
	Page* page;
	Page* page2;
};

