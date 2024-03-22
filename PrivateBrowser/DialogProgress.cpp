#include "DialogProgress.h"
#include <thread>
#include <chrono>
DialogProgress::DialogProgress() {
    HRESULT hr = CoCreateInstance(CLSID_ProgressDialog, NULL, CLSCTX_INPROC_SERVER, IID_IProgressDialog,(LPVOID*)&dialog);
    if (FAILED(hr))
    {
        dialog = NULL;
        return;
    }
    dialog->SetTitle(L"ϵͳ��ʾ");
    dialog->SetAnimation(NULL, 32);
    dialog->SetLine(2, L"�״�ִ����Ҫ��ʼ�����л���", FALSE, NULL);
    dialog->StartProgressDialog(NULL, NULL, PROGDLG_MODAL | PROGDLG_MARQUEEPROGRESS, NULL);
    std::thread t(&DialogProgress::checkUserCancel, this);
    t.detach();
}
DialogProgress::~DialogProgress() {
    dialog->Release();    
}

void DialogProgress::checkUserCancel() {
    while (!dialog->HasUserCancelled())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1200));
    }
    dialog->StopProgressDialog();
    exit(0);
}