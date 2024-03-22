#pragma once
#include <string>
#include <Windows.h>

std::string ConvertToUTF8(const std::wstring& wstr);
std::string ConvertToUTF8(const LPWSTR& wstr);
void ChangeCursor(LPCTSTR cursor);
void Debug(const std::string& info);

