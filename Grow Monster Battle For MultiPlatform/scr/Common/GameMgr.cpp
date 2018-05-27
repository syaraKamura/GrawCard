﻿/*
				ファイル名		:SceneMgr.cpp
				作成者			:
				作成日時		:2017/12/11
				ソース説明		:ゲーム管理クラス

				
				
				備考
					
				
!*/

#include "Common/GameCommon.h"
#include "Common/GameMgr.h"
#include "Scene/SceneMgr.h"
#include "Common/FPS/FPS.h"

GameMgr::GameMgr(){

	int fps = 0;

#ifdef __WINDOWS__
	fps = 60;
#elif __ANDROID__
	fps = 60;
#endif
	
	mFPS = new FPS(fps,fps);
#ifdef __MY_DEBUG__
	mDebug = new Debug();
	mSceneMgr = new SceneMgr(mDebug);
#else
	mSceneMgr = new SceneMgr();
#endif
	ComRes::Create();
}

GameMgr::~GameMgr(){
	ComRes::Destory();

	Delete(mSceneMgr);
	Delete(mFPS);
#ifdef __MY_DEBUG__
	Delete(mDebug);
#endif

}

void GameMgr::Initialize(){
	TaskMgr::getInstance().Initialize();
	mSceneMgr->Initialize();

#ifdef __MY_DEBUG__
	mDebug->Initialize();
#endif

#ifdef __MY_WINDOWS__
	Keyboard_Initialize();
	Mouse_Initialize();
#endif

	

}

void GameMgr::Finalize(){
	TaskMgr::getInstance().Finalize();
	mSceneMgr->Finalize();

#ifdef __MY_DEBUG__
	mDebug->Finalize();
#endif

#ifdef __MY_WINDOWS__
	Keyboard_Finalize();
	Mouse_Finalize();
#endif

}

void GameMgr::PreviousUpdate() {
	mSceneMgr->PreviousUpdate();
	TaskMgr::getInstance().PreviousUpdate();
}

void GameMgr::InputUpdate() {
	
#ifdef __MY_WINDOWS__
	Keyboard_Updata();
	Mouse_Updata();
#else
	Touch_Updata();
#endif


}

bool GameMgr::Updata(){


	mFPS->Updata();

#ifdef __MY_DEBUG__
	if (mDebug->Updata() == true) {
		return true;
	}

	if (ComRes::Instance()->IsError()) {
		return false;
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

	

	

}

void GameMgr::PostUpdate() {
	TaskMgr::getInstance().LateUpdata();

	mFPS->Wait();
}