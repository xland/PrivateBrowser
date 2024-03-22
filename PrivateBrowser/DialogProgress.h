#pragma once
#include <Windows.h>
#include <CommCtrl.h>
#include <shlobj_core.h>
#pragma comment(linker,"\"/manifestdependency:type='win32' \
    name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
    processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
class DialogProgress
{
public:
	DialogProgress();
	~DialogProgress();
private:
	void checkUserCancel();
	IProgressDialog* dialog{nullptr};
};

