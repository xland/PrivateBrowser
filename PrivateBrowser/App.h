#pragma once
#include <memory>
#include <vector>
#include "WindowMain.h"
#include "EnvironmentBox.h"
class App
{
public:
	~App();
	static void Init(const HINSTANCE& hInstance);
	static void Dispose();
	static App* get();
	static SkFont* getIconFont();
	static SkFont* getTextFont();
	WindowMain* windowMain;
private:
	App(const HINSTANCE& hInstance);
	void initFontIcon();
};

