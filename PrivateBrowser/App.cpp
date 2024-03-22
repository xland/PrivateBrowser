#include "App.h"
#include "WindowMain.h"

namespace {
	static App* app;
}

App::App(const HINSTANCE& hInstance):hinstance{ hInstance }
{
	auto win = new WindowMain();
	windows.push_back(win);
	EnvironmentBox::Init([&win]() {
		win->CreatePageController();
	});
}
App::~App()
{

}
void App::Init(const HINSTANCE& hInstance) {
	if (app) {
		return;
	}
	app = new App(hInstance);
}
App* App::Get() {
	return app;
}
void App::Dispose()
{
	delete app;
}