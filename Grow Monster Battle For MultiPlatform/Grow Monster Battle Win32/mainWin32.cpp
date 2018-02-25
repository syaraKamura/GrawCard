#include "Common/GameCommon.h"
#include "Common/Framework.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	Framework frame(new GameMgr());

	if (frame.Initialize(WINDOW_WIDTH, WINDOW_HEIGHT, "Grow Card ver0.0.0", true)) {
		frame.Run();
	}

	frame.Finalize();
	return 0;
}
