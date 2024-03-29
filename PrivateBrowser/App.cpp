#include "App.h"
#include <Windows.h>
#include <include/core/SkData.h>
#include <memory>
#include <include/core/SkFont.h>
#include <include/core//SkFontMgr.h>
#include <include/core/SkFontStyle.h>
#include <include/core/SkGraphics.h>
#include <include/ports/SkTypeface_win.h>
#include "res.h"
#include "WindowMain.h"

namespace {
	static App* app;
    std::shared_ptr<SkFont> fontIcon{ nullptr };
    std::shared_ptr<SkFont> fontText{ nullptr };
    sk_sp<SkFontMgr> fontMgr;
}

App::App(const HINSTANCE& hInstance)
{
    fontMgr = SkFontMgr_New_GDI();
    initFontIcon();
	windowMain = new WindowMain(hInstance);
}
App::~App()
{

}
void App::Init(const HINSTANCE& hInstance) {
	if (app) {
		return;
	}
	app = new App(hInstance);
    EnvironmentBox::Init([]() {
        App::get()->windowMain->CreatePageController();
    });
}
App* App::get() {
	return app;
}
void App::Dispose()
{
	delete app;
}
SkFont* App::getIconFont()
{
    return fontIcon.get();
}

SkFont* App::getTextFont()
{
    return fontText.get();
}
void App::initFontIcon()
{
    HMODULE instance = GetModuleHandle(NULL);
    HRSRC resID = FindResource(instance, MAKEINTRESOURCE(IDR_ICON_FONT), L"ICON_FONT");
    if (resID == 0)
    {
        MessageBox(NULL, L"查找字体图标资源失败", L"系统提示", NULL);
        return;
    }
    size_t resSize = SizeofResource(instance, resID);
    HGLOBAL res = LoadResource(instance, resID);
    if (res == 0)
    {
        MessageBox(NULL, L"加载字体图标资源失败", L"系统提示", NULL);
        return;
    }
    LPVOID resData = LockResource(res);
    auto fontData = SkData::MakeWithoutCopy(resData, resSize);
    fontIcon = std::make_shared<SkFont>(fontMgr->makeFromData(fontData));
}