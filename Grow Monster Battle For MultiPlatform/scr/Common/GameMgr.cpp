/*
				ファイル名		:SceneMgr.cpp
				作成者			:
				作成日時		:2017/12/11
				ソース説明		:ゲーム管理クラス

				
				
				備考
					
				
!*/

#include "Common/GameCommon.h"
#include "Common/GameMgr.h"
#include "Scene/SceneMgr.h"
#include "Common/Task/Task.h"
#include "Common/FPS/FPS.h"
#include "Common/Debug/Debug.h"

GameMgr::GameMgr(){
	mSceneMgr = new SceneMgr();
	mFPS = new FPS(60);
	mDebug = new Debug();
}

GameMgr::~GameMgr(){
	Delete(mSceneMgr);
	Delete(mFPS);
	Delete(mDebug);
}

void GameMgr::Initialize(){
	TaskMgr::getInstance().Initialize();
	mSceneMgr->Initialize();
	mDebug->Initialize();

#ifdef __MY_WINDOWS__
	Keyboard_Initialize();
#endif

}

void GameMgr::Finalize(){
	TaskMgr::getInstance().Finalize();
	mSceneMgr->Finalize();
	mDebug->Finalize();

#ifdef __MY_WINDOWS__
	Keyboard_Finalize();
#endif

}

bool GameMgr::Updata(){


	mFPS->Updata();

#ifdef __MY_WINDOWS__
	Keyboard_Updata();
#else
	Touch_Updata();
#endif

#ifdef __MY_DEBUG__
	if (mDebug->Updata() == true) {
		return true;
	}
#endif

	mSceneMgr->Updata();
	TaskMgr::getInstance().Updata();
	return true;
}

void GameMgr::Draw(){
	mSceneMgr->Draw();
	
	TaskMgr::getInstance().Draw();
	mFPS->Draw();

#ifdef __MY_DEBUG__
	mDebug->Draw();
#endif

	TaskMgr::getInstance().LateUpdata();

	mFPS->Wait();

}