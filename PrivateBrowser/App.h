#pragma once
#include <memory>
#include <vector>
#include "WindowBase.h"
#include "EnvironmentBox.h"
class App
{
public:
	~App();
	static void Init(const HINSTANCE& hInstance);
	static void Dispose();
	static App* Get();
	HINSTANCE hinstance;
private:
	App(const HINSTANCE& hInstance);
	std::vector<WindowBase*> windows;
};

