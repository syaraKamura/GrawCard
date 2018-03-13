#include "Common/GameCommon.h"
#include "Common/Framework.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	Framework frame(new GameMgr());
	bool isWindowMode = true;
#ifndef __MY_DEBUG__
	int ret = MessageBox(NULL, _T("ウィンドウモードで実行？"), _T("ウィンドウモード"), MB_YESNO);
	isWindowMode = (ret == IDYES) ;
#endif

	if (frame.Initialize(WINDOW_WIDTH, WINDOW_HEIGHT, "Grow Card ver0.0.0", isWindowMode)) {
		frame.Run();
	}

	frame.Finalize();
	return 0;
}
