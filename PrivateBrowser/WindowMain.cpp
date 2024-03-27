﻿#include "WindowMain.h"
#include <windowsx.h>
#include <WebView2.h>
#include <wrl.h>
#include <wil/com.h>
#include <dwmapi.h>
#include "EnvironmentBox.h"
using namespace Microsoft::WRL;

WindowMain::WindowMain() {
    long w{ 1200 }, h{ 800 };
    RECT rect;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
    int x = (rect.right - w) / 2;
    int y = (rect.bottom - h) / 2;
    InitWindow(x, y, w, h, L"靠谱");
}
WindowMain::~WindowMain() {

}

void WindowMain::paintWindow()
{
    //PAINTSTRUCT ps;
    //auto dc = BeginPaint(hwnd, &ps);
    //auto c = canvas.get();
    //for (size_t i = 0; i < ctrls.size(); i++)
    //{
    //    ctrls[i]->paint(c);
    //}
    //BITMAPINFO* bmpInfo = reinterpret_cast<BITMAPINFO*>(surfaceMemory.get());
    //StretchDIBits(dc, 0, 0, w, h, 0, 0, w, h, bmpInfo->bmiColors, bmpInfo, DIB_RGB_COLORS, SRCCOPY);
    //ReleaseDC(hwnd, dc);
    //EndPaint(hwnd, &ps);
    //surfaceMemory.reset(0); //实践证明这样即节省内存，速度也不会慢
}

void WindowMain::InitWindow(const int& x, const int& y, const long& w, const long& h, const std::wstring& title)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    static int num = 0;
    std::wstring winName = L"PrivateBrowser";
    auto clsName = std::format(L"{}_{}", winName, num++);
    auto hinstance = GetModuleHandle(NULL);
    WNDCLASSEX wcx{};
    wcx.cbSize = sizeof(wcx);
    wcx.style = CS_HREDRAW | CS_VREDRAW;
    wcx.lpfnWndProc = &WindowMain::RouteWindowMessage;
    wcx.cbWndExtra = sizeof(WindowMain*);
    wcx.hInstance = hinstance;
    wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcx.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcx.lpszClassName = clsName.c_str();
    if (!RegisterClassEx(&wcx))
    {
        MessageBox(NULL, L"注册窗口类失败", L"系统提示", NULL);
        return;
    }
    hwnd = CreateWindowEx(NULL, wcx.lpszClassName, title.c_str(),
        WS_OVERLAPPEDWINDOW, x, y, w, h, NULL, NULL, hinstance, static_cast<LPVOID>(this));
    SetWindowPos(hwnd, nullptr, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
    const MARGINS shadowState{ 1,1,1,1 };
    DwmExtendFrameIntoClientArea(hwnd, &shadowState);
    Show();
}

bool WindowMain::CreatePageController()
{
    auto callBackInstance = Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(this, &WindowMain::pageCtrlCallBack);
    auto env = EnvironmentBox::Get()->Environment;
    auto result = env->CreateCoreWebView2Controller(hwnd, callBackInstance.Get());
    if (FAILED(result)) {
        return false;
    }
    return true;
}
HRESULT WindowMain::pageCtrlCallBack(HRESULT result, ICoreWebView2Controller* controller)
{
    static bool flag = true;
    HRESULT hr;
    if (flag) {
        this->controller = controller;
        wil::com_ptr<ICoreWebView2> webview;
        hr = controller->get_CoreWebView2(&webview);
        page = new Page(webview, this);
        RECT bounds{ .left{0},
        .top{40},
        .right{w-200},
        .bottom{h} };
        hr = controller->put_Bounds(bounds);
    }
    else {
        this->controller2 = controller;
        wil::com_ptr<ICoreWebView2> webview;
        hr = controller2->get_CoreWebView2(&webview);
        page2 = new Page(webview, this);
        RECT bounds{ .left{200},
        .top{200},
        .right{600},
        .bottom{600} };
        hr = controller2->put_Bounds(bounds);
        //controller2->getwindowha
        //SetWindowPos(hwnd2, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    }
    flag = false;
    return hr;
}
void WindowMain::Show() {
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    //CreateCoreWebView2EnvironmentWithOptions(nullptr, nullptr, nullptr,
    //    Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(
    //        [this](HRESULT result, ICoreWebView2Environment* env) -> HRESULT {
    //            // Create a CoreWebView2Controller and get the associated CoreWebView2 whose parent is the main window hWnd
    //            env->CreateCoreWebView2Controller(hwnd, Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(
    //                [this](HRESULT result, ICoreWebView2Controller* controller) -> HRESULT {
    //                    if (controller != nullptr) {
    //                        webviewController = controller;
    //                        webviewController->get_CoreWebView2(&webview);
    //                    }
    //                    // Add a few settings for the webview
    //                    // The demo step is redundant since the values are the default settings
    //                    wil::com_ptr<ICoreWebView2Settings> settings;
    //                    webview->get_Settings(&settings);
    //                    settings->put_IsScriptEnabled(TRUE);
    //                    settings->put_AreDefaultScriptDialogsEnabled(TRUE);
    //                    settings->put_IsWebMessageEnabled(TRUE);
    //                    // Resize WebView to fit the bounds of the parent window
    //                    RECT bounds;
    //                    GetClientRect(hwnd, &bounds);
    //                    webviewController->put_Bounds(bounds);
    //                    // Schedule an async task to navigate to Bing
    //                    webview->Navigate(L"file:///D:/project/PrivateBrowser/ui/src/index.html");
    //                    return S_OK;
    //                }).Get());
    //            return S_OK;
    //        }).Get());
}

LRESULT CALLBACK WindowMain::RouteWindowMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_NCCREATE)
    {
        CREATESTRUCT* pCS = reinterpret_cast<CREATESTRUCT*>(lParam);
        LPVOID pThis = pCS->lpCreateParams;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
    }
    auto obj = reinterpret_cast<WindowMain*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    if (obj) {
        return obj->WindowProc(hWnd, msg, wParam, lParam);
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK WindowMain::WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static bool mouseTracing = false;
    switch (msg)
    {
    case WM_NCCALCSIZE:
    {
        return false;
    }
    //case WM_ERASEBKGND: {
    //    return false;
    //}
    //case WM_PAINT: {
    //    paintWindow();
    //    return true;
    //}
    case WM_EXITSIZEMOVE: {
        RECT rect;
        GetWindowRect(hWnd, &rect);
        this->x = rect.left;
        this->y = rect.top;
        return true;
    }
    case WM_SIZE: {
        if (lParam != 0 && controller != nullptr) {
            RECT rect;
            GetClientRect(hWnd, &rect);
            controller->put_Bounds(rect);
        };
        break;
    }
    case WM_DESTROY: {
        PostQuitMessage(0);
        break;
    }
    }
    return DefWindowProcW(hWnd, msg, wParam, lParam);
}