#include <dwmapi.h>
#include <Windows.h>
#include <windowsx.h>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>
#include <QTextEdit>
#include <QGraphicsDropShadowEffect>
#include <QWebEngineView>
#include <QObject>
#include <QWindow>

#include "PrivateBrowser.h"
#include "TitleBar.h"
#include "LeftBar.h"

PrivateBrowser::PrivateBrowser(QWidget *parent)
    : QMainWindow(parent)
{
    qDebug() << "allen!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
    setWindowFlags(Qt::FramelessWindowHint);
    setMinimumSize(1200, 800);

    auto container = new QWidget(this);
    setCentralWidget(container);

    auto winLayout = new QVBoxLayout(container);
    winLayout->setContentsMargins(0, 0, 0, 0);
    winLayout->setSpacing(0);
    container->setLayout(winLayout);

    winLayout->addWidget(new TitleBar(container));
    auto splitter = new QSplitter(Qt::Horizontal, container);
    splitter->setSizes({100, width() - 100});
    winLayout->addWidget(splitter);

    // splitter->setObjectName("splitter");
    // splitter->setStyleSheet(R"(#splitter{border:0.5px solid #333;border-top:none;})");
    auto leftBar = new LeftBar(splitter);
    splitter->addWidget(leftBar);
    {
        auto *webView = new QWebEngineView(splitter);
        webView->setBackgroundRole(QPalette::ColorRole::Dark);
        webView->setUrl(QUrl("https://www.baidu.com"));
        // webView->setHtml("<html><head></head><body>测试abc</body></html>");
        webView->show();
        // 连接QWebEnginePage的loadFinished信号到自定义槽函数
        // connect(webView, &QWebEngineView::loadFinished, [this](bool ok)
        //         {
        //         auto a = 1;
        //         this->clearFocus(); });

        splitter->addWidget(webView);
    }
    HWND hwnd = (HWND)winId();
    DWMNCRENDERINGPOLICY policy = DWMNCRP_ENABLED;
    DwmSetWindowAttribute(hwnd, DWMWA_NCRENDERING_POLICY, &policy, sizeof(policy));
    MARGINS margins = {1, 1, 1, 1};
    DwmExtendFrameIntoClientArea(hwnd, &margins);
}

PrivateBrowser::~PrivateBrowser()
{
}

bool PrivateBrowser::nativeEvent(const QByteArray &eventType, void *message, qintptr *result)
{
    MSG *msg = static_cast<MSG *>(message);
    if (msg && msg->message == WM_NCHITTEST)
    {
        // 此处Qt的mapFromGlobal得不到正确的坐标，必须使用系统API获取正确坐标
        POINT pt;
        pt.x = GET_X_LPARAM(msg->lParam);
        pt.y = GET_Y_LPARAM(msg->lParam);
        ScreenToClient((HWND)winId(), &pt);
        int hitTestResult = ncTest(pt.x, pt.y);
        *result = hitTestResult;
        return true; // 表示已处理该消息
    }
    return false;
}

int PrivateBrowser::ncTest(const int &x, const int &y)
{
    // 此处必须使用系统API获取正确窗口大小，正确窗口大小比1200, 800要大
    RECT r;
    GetClientRect((HWND)winId(), &r);
    int size{6}, w{r.right}, h{r.bottom};
    if (x < size && y < size)
    {
        return HTTOPLEFT;
    }
    else if (x > size && y < size && x < w - size)
    {
        return HTTOP;
    }
    else if (y < size && x > w - size)
    {
        return HTTOPRIGHT;
    }
    else if (y > size && y < h - size && x > w - size)
    {
        return HTRIGHT;
    }
    else if (y > h - size && x > w - size)
    {
        return HTBOTTOMRIGHT;
    }
    else if (x > size && y > h - size && x < w - size)
    {
        return HTBOTTOM;
    }
    else if (x < size && y > h - size)
    {
        return HTBOTTOMLEFT;
    }
    else if (x < size && y < h - size && y > size)
    {
        return HTLEFT;
    }
    else
    {
        return HTCLIENT;
    }
}
