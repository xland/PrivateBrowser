#pragma once
#include <Windows.h>
#include <string>
#include <format>
#include <wrl.h>
#include <wil/com.h>
#include <WebView2.h>
#include "Page.h"
#include "ControlBase.h"


class WindowMain
{
public:
	WindowMain();
	~WindowMain();
	void Show();
	void InitWindow(const int& x, const int& y, const long& w, const long& h, const std::wstring& title);
	bool CreatePageController();
	std::vector<ControlBase*> ctrls;
	HWND hwnd;
	wil::com_ptr<ICoreWebView2Controller> controller;
	wil::com_ptr<ICoreWebView2Controller> controller2;
protected:
	void paintWindow();
private:
	static LRESULT CALLBACK RouteWindowMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	HRESULT pageCtrlCallBack(HRESULT result, ICoreWebView2Controller* controller);
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	long w, h;
	int x, y;
	void* pixelData;
	unsigned long pixelDataSize;
	HBITMAP bitmap;
	HDC compatibleDC = NULL;
	Page* page;
	Page* page2;
};

