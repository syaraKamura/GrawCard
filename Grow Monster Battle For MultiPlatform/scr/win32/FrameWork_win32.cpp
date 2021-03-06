﻿/*
				ファイル名		:FrameWork_win32.cpp
				作成者			:
				作成日時		:2018/02/25
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "Common/Framework.h"


#ifdef __WINDOWS__

Framework::Framework(GameMgr* game) {
	SetWindowSizeChangeEnableFlag(true);
	mGameMgr = game;
}

Framework::~Framework() {
	
}


bool Framework::Initialize(int width, int height, const char* titleName/* = ""*/, bool isWindowMode/* = true*/) {

	//初期設定

	SetWindowText(titleName);
	//SetUseCharCodeFormat(DX_CHARCODEFORMAT_UTF8);
	SetGraphMode(width, height, 32);
	
	if (isWindowMode == true) {
		ChangeWindowMode(TRUE);
#ifdef __MY_DEBUG__
		SetWindowInitPosition(2350, 0);
#endif // __MY_DEBUG__
	}
	else {
		SetMouseDispFlag(TRUE);
		SetMousePoint(width / 2, height / 2);
	}
	
	if (DxLib_Init() == -1) {
		Debug::ErorrMessage("DxLibの初期化に失敗しました。\n終了します。");
		exit(99);
		DxLib_End();
		return false;
	}
	
	SetUseDirect3DVersion(DX_DIRECT3D_9);

#ifdef __MY_DEBUG__
	SetAlwaysRunFlag(TRUE);
#endif

	SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定

	if (mGameMgr == NULL) {
		Debug::ErorrMessage("mGameMgrにNULLが渡されました。\n終了します。");
		exit(99);
		DxLib_End();
		return false;
	}
	
	mGameMgr->Initialize();
	
	return true;
}

void Framework::Finalize() {
	mGameMgr->Finalize();
	Delete(mGameMgr);
	DxLib_End();
}

void Framework::Run() {
	
	// while( 裏画面を表画面に反映, メッセージ処理, 画面クリア, )
	while (/*ScreenFlip() == 0 && */ProcessMessage() == 0 && ClearDrawScreen() == 0 && Keyboard_Off(KEY_INPUT_ESCAPE)) {

		mGameMgr->PreviousUpdate();
		mGameMgr->InputUpdate();

		if (mGameMgr->Updata() == false) {
			break;
		}

		mGameMgr->Draw();
		ScreenFlip();
		mGameMgr->PostUpdate();

	}
}


#endif	//__WINDOWS__