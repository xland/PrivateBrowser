#pragma once
#include <windows.h>
#include <Shlobj.h>
#include <shellapi.h>
#include <fstream>
#include <filesystem>
#include <functional>
#include <wrl.h>
#include <wil/com.h>
#include <WebView2.h>
//todo 首次使用本应用需要初始化环境
class EnvironmentBox
{
public:
	static bool Init(const std::function<void()> func);
	static EnvironmentBox* Get();
	HRESULT callBack(HRESULT result, ICoreWebView2Environment* env);
	ICoreWebView2Environment* Environment;
private:
	std::filesystem::path ensureAppFolder();
	bool checkRegKey(const HKEY& key, const std::wstring& subKey);
	bool checkRuntime();
	std::function<void()> func;
};

