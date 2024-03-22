#include "WindowMain.h"

WindowMain::WindowMain() {
    long w{ 1000 }, h{ 700 };
    RECT rect;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
    int x = (rect.right - w) / 2;
    int y = (rect.bottom - h) / 2;
    InitWindow(x, y, w, h, L"靠谱");
}
WindowMain::~WindowMain() {

}