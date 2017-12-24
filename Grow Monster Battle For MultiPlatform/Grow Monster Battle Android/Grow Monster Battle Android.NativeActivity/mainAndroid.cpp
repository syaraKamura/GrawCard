#include"Common/GameCommon.h"
#include "Common/GameMgr.h"

//#ifndef __ANDROID__

// プログラムは android_main から始まります
int android_main(void)
{
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);
	
	DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定
	
	GameMgr gameMgr;

	gameMgr.Initialize();


	// while( 裏画面を表画面に反映, メッセージ処理, 画面クリア, )
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {



		gameMgr.Updata();
		gameMgr.Draw();

	}

	gameMgr.Finalize();
	
	DxLib_End(); // DXライブラリ終了処理
	return 0;
}

//#endif
