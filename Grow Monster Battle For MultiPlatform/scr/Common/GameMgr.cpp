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

GameMgr::GameMgr(){
	mSceneMgr = new SceneMgr();
	mFPS = new FPS(60);
}

GameMgr::~GameMgr(){
	Delete(mSceneMgr);
	Delete(mFPS);
}

void GameMgr::Initialize(){
	TaskMgr::getInstance().Initialize();
	mSceneMgr->Initialize();
}

void GameMgr::Finalize(){
	TaskMgr::getInstance().Finalize();
	mSceneMgr->Finalize();
}

bool GameMgr::Updata(){

	mFPS->Updata();

#ifdef __MY_WINDOWS__
	Keyboard_Updata();
#else
	Touch_Updata();
#endif

	mSceneMgr->Updata();
	TaskMgr::getInstance().Updata();
	return true;
}

void GameMgr::Draw(){
	mSceneMgr->Draw();
	
	TaskMgr::getInstance().Draw();
	mFPS->Draw();

	TaskMgr::getInstance().LateUpdata();

	mFPS->Wait();

}