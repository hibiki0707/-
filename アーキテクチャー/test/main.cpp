#include <DxLib.h>
#include <algorithm>

int WINAPI WinMain(_In_ HINSTANCE,_In_opt_ HINSTANCE,_In_ LPSTR,_In_ int) {
	
	int lval = 3;
	int rval = 5;
	auto minval = std::min(lval, rval);
	auto maxval = std::max(lval, rval);

	SetGraphMode(1280, 720, 32);
	ChangeWindowMode(true);
	SetWindowText(_T("1916002_çrñÿ"));
	if (DxLib_Init()) return -1;
	SetDrawScreen(DX_SCREEN_BACK);

	while (ProcessMessage() != -1) {
		ClearDrawScreen();
		ScreenFlip();
	}
	return 0;
	DxLib_End();
}