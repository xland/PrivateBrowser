#include "WindowMain.h"
#include <windowsx.h>
#include <WebView2.h>
#include <wrl.h>
#include <wil/com.h>
#include <dwmapi.h>
#include "App.h"
#include "EnvironmentBox.h"
#include "TitleBar.h"
#include "SideBar.h"
using namespace Microsoft::WRL;

WindowMain::WindowMain(const HINSTANCE& hInstance) {
    RECT rect;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
    x = (rect.right - w) / 2;
    y = (rect.bottom - h) / 2;
    ctrls.push_back(new TitleBar());
    ctrls.push_back(new SideBar());
    initWindow(hInstance);
}
WindowMain::~WindowMain() {
    for (auto ctrl : ctrls)
    {
        delete ctrl;
    }
}

void WindowMain::paintWindow()
{    
    PAINTSTRUCT ps;
    BeginPaint(hwnd, &ps);
    if (ps.rcPaint.top == ctrls[0]->rect.fBottom) {
        //todo 创建浏览器控件之后，也会导致一次刷新
        return;
    }
    auto c = canvas.get();
    for (size_t i = 0; i < ctrls.size(); i++)
    {
        ctrls[i]->paint(c);
    }
    BITMAPINFO* bmpInfo = reinterpret_cast<BITMAPINFO*>(surfaceMemory.get());
    //todo 这里是有问题的
    StretchDIBits(ps.hdc, 0, 0, w, h, 0, 0, w, h, 
        bmpInfo->bmiColors, bmpInfo, DIB_RGB_COLORS, SRCCOPY);
    EndPaint(hwnd, &ps);
    //surfaceMemory.reset(0); //实践证明这样即节省内存，速度也不会慢
}

void WindowMain::onSize(const int& w, const int& h)
{
    this->w = w;
    this->h = h;
    auto rowSize{ 4 * w };
    size_t bmpSize = sizeof(BITMAPINFOHEADER) + h * rowSize;
    surfaceMemory.reset(bmpSize);
    BITMAPINFO* bmpInfo = reinterpret_cast<BITMAPINFO*>(surfaceMemory.get());
    ZeroMemory(bmpInfo, sizeof(BITMAPINFO));
    bmpInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmpInfo->bmiHeader.biWidth = w;
    bmpInfo->bmiHeader.biHeight = -h; // negative means top-down bitmap. Skia draws top-down.
    bmpInfo->bmiHeader.biPlanes = 1;
    bmpInfo->bmiHeader.biBitCount = 32;
    bmpInfo->bmiHeader.biCompression = BI_RGB;
    void* pixels = bmpInfo->bmiColors;
    SkImageInfo info = SkImageInfo::MakeN32Premul(w, h);
    auto temp = SkCanvas::MakeRasterDirect(info, pixels, rowSize);
    canvas = std::move(temp);
    for (size_t i = 0; i < ctrls.size(); i++)
    {
        ctrls[i]->resize(w, h);
    }
    if (controller) {
        RECT bounds{ .left{0}, .top{(LONG)ctrls[0]->rect.fBottom}, .right{w - 300}, .bottom{h} };
        controller->SetBoundsAndZoomFactor(bounds, 1.0);
    }
}

void WindowMain::mouseMove(const int& x, const int& y)
{
    if (!isTrackMouseEvent) {
        TRACKMOUSEEVENT tme = {};
        tme.cbSize = sizeof(TRACKMOUSEEVENT);
        tme.dwFlags = TME_HOVER | TME_LEAVE;
        tme.hwndTrack = hwnd;
        tme.dwHoverTime = 1;
        isTrackMouseEvent = TrackMouseEvent(&tme);
    }
    ControlBase* ctrl{ nullptr };
    for (size_t i = 0; i < ctrls.size(); i++)
    {
        ctrl = ctrls[i]->contain(x, y);
        if (ctrl) {
            if (hoverCtrl && ctrl != hoverCtrl) {
                hoverCtrl->mouseOut(x,y);
            }
            hoverCtrl = ctrl;
            ctrl->mouseEnter(x, y);
            break;
        }
    }
}

void WindowMain::initWindow(const HINSTANCE& hInstance)
{
    static int num = 0;
    std::wstring title = L"Private Browser";
    auto clsName = std::format(L"{}_{}", title, num++);
    WNDCLASSEX wcx{};
    wcx.cbSize = sizeof(wcx);
    wcx.style = CS_HREDRAW | CS_VREDRAW;
    wcx.lpfnWndProc = &WindowMain::RouteWindowMessage;
    wcx.cbWndExtra = sizeof(WindowMain*);
    wcx.hInstance = hInstance;
    wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcx.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcx.lpszClassName = clsName.c_str();
    if (!RegisterClassEx(&wcx))
    {
        MessageBox(NULL, L"注册窗口类失败", L"系统提示", NULL);
        return;
    }
    hwnd = CreateWindowEx(NULL, wcx.lpszClassName, title.c_str(), WS_VISIBLE| WS_OVERLAPPEDWINDOW,
        x, y, w, h, NULL, NULL, hInstance, static_cast<LPVOID>(this));
    DWMNCRENDERINGPOLICY policy = DWMNCRP_ENABLED;
    DwmSetWindowAttribute(hwnd, DWMWA_NCRENDERING_POLICY, &policy, sizeof(policy));
    MARGINS margins = { 1,1,1,1 };
    DwmExtendFrameIntoClientArea(hwnd, &margins);
    
}

bool WindowMain::CreatePageController()
{
    auto callBackInstance = Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(this, &WindowMain::pageCtrlCallBack);
    auto env = EnvironmentBox::Get()->env;
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
        RECT bounds{ .left{0}, .top{(LONG)ctrls[0]->rect.fBottom}, .right{w - 300}, .bottom{h}};
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
void WindowMain::show() {
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    // 
    // 
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
        return obj->wndProc(hWnd, msg, wParam, lParam);
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK WindowMain::wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static bool mouseTracing = false;
    switch (msg)
    {
    case WM_NCCALCSIZE:
    {
        return false;
    }
    case WM_GETMINMAXINFO:
    {
        MINMAXINFO* mminfo = (PMINMAXINFO)lParam;
        RECT workArea;
        SystemParametersInfo(SPI_GETWORKAREA, 0, &workArea, 0);
        mminfo->ptMinTrackSize.x = 1200;
        mminfo->ptMinTrackSize.y = 800;
        mminfo->ptMaxSize.x = workArea.right - workArea.left-2;
        mminfo->ptMaxSize.y = workArea.bottom - workArea.top-2;
        mminfo->ptMaxPosition.x = 1;
        mminfo->ptMaxPosition.y = 1;
        return true;
    }
    case WM_ERASEBKGND: {
        return false;
    }
    case WM_PAINT: {
        paintWindow();
        return true;
    }
    case WM_NCHITTEST: {
        POINT pt;
        pt.x = GET_X_LPARAM(lParam);
        pt.y = GET_Y_LPARAM(lParam);
        ScreenToClient(hWnd, &pt);
        return nctest(pt.x, pt.y);
    }
    case WM_EXITSIZEMOVE: {
        RECT rect;
        GetWindowRect(hWnd, &rect);
        this->x = rect.left;
        this->y = rect.top;
        return true;
    }
    case WM_SIZE: {
        onSize(LOWORD(lParam), HIWORD(lParam));
        return true;
    }
    case WM_MOUSELEAVE: {
        if (!isMouseDown) {
            TRACKMOUSEEVENT tme = {};
            tme.cbSize = sizeof(TRACKMOUSEEVENT);
            tme.dwFlags = TME_CANCEL | TME_HOVER | TME_LEAVE;
            tme.hwndTrack = hwnd;
            TrackMouseEvent(&tme);
            isTrackMouseEvent = false;            
        }
        if (hoverCtrl) {
            hoverCtrl->mouseOut(-1,-1);
            hoverCtrl = nullptr;
        }
        isMouseDown = false;
        return true;
    }
    case WM_LBUTTONDOWN:
    {
        isMouseDown = true;
        if (hoverCtrl) {
            hoverCtrl->mouseDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        }
        if (ctrls[0]->ctrls[0]->hoverIndex == 99 && ctrls[0]->ctrls[0] != hoverCtrl) {
            ctrls[0]->ctrls[0]->hoverIndex = -1;
            ctrls[0]->ctrls[0]->repaint();
        }
        return true;
    }
    case WM_LBUTTONUP:
    {
        hoverCtrl->mouseUp(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        isMouseDown = false;
        break;
    }
    case WM_MOUSEMOVE:
    {
        if (isMouseDown) {
            hoverCtrl->mouseDrag(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        }
        else
        {
            mouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        }        
        break;
    }
    case WM_DESTROY: {
        PostQuitMessage(0);
        break;
    }
    }
    return DefWindowProcW(hWnd, msg, wParam, lParam);
}

int WindowMain::nctest(const int& x, const int& y)
{
    int size{ 6 };
    if (x < size && y < size) {
        return HTTOPLEFT;
    }
    else if (x > size && y < size && x < w - size) {
        return HTTOP;
    }
    else if (y < size && x > w - size) {
        return HTTOPRIGHT;
    }
    else if (y > size && y<h - size && x > w - size) {
        return HTRIGHT;
    }
    else if (y > h - size && x > w - size) {
        return HTBOTTOMRIGHT;
    }
    else if (x > size && y > h - size && x < w - size) {
        return HTBOTTOM;
    }
    else if (x < size && y > h - size) {
        return HTBOTTOMLEFT;
    }
    else if (x < size && y < h - size && y>size) {
        return HTLEFT;
    }
    else {
        if (!isTrackMouseEvent) {
            SetCursor(LoadCursor(nullptr, IDC_ARROW));
        }
        return HTCLIENT;
    }
}
