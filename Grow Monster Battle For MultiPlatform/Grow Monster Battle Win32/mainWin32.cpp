#include "Common/GameCommon.h"
#include "Common/GameMgr.h"

#ifdef __WINDOWS__
// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetWindowText("Grow Card ver0.0.0");
	//SetUseCharCodeFormat(DX_CHARCODEFORMAT_UTF8);
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定


	GameMgr gameMgr;

	gameMgr.Initialize();


	// while( 裏画面を表画面に反映, メッセージ処理, 画面クリア, )
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && Keyboard_Off(KEY_INPUT_ESCAPE)) {


		gameMgr.Updata();
		gameMgr.Draw();

	}

	gameMgr.Finalize();

	DxLib_End(); // DXライブラリ終了処理
	return 0;
}
#endif