﻿/*
				ファイル名		:SceneMgr.cpp
				作成者			:
				作成日時		:2017/12/11
				ソース説明		:ゲーム管理クラス

				
				
				備考
					
				
!*/

#include "Common/GameCommon.h"
#include "Common/GameMgr.h"
#include "Common/FileLoader/TblLoader/TblLoaderMgr.h"
#include "Common/Effect/Effect.h"
#include "Scene/SceneMgr.h"
#include "Common/FPS/FPS.h"

#include "Scene/MainMenu/Dungeon/DungeonMgr.h"


#ifdef __WINDOWS__
static const int BASE_FPS = 60;	//基本フレームレート
#elif __ANDROID__
static const int BASE_FPS = 30;
#endif

GameMgr::GameMgr(){

	int fps = BASE_FPS;
	
	mFPS = new FPS(fps,fps);
#ifdef __MY_DEBUG__
	mDebug = new Debug();
	mSceneMgr = new SceneMgr(mDebug);
#else
	mSceneMgr = new SceneMgr();
#endif

	TaskMgr::getInstance().Initialize();

	loader::TblLoaderMgr::Create();

#ifdef __MY_WINDOWS__
#ifdef ENABLE_EFFEKSEER
	EffekseerEffect::EffectLoader::Create();
#endif // ENABLE_EFFEKSEER
#endif

	Effect::EffectMgr::Create();

	SoundMgr::Create();
	ComRes::Create();
	DungeonMgr::Create();
	ClickInput::Create();
}

GameMgr::~GameMgr(){

#ifdef __MY_WINDOWS__
#ifdef ENABLE_EFFEKSEER
	EffekseerEffect::EffectLoader::Destroy();
#endif // ENABLE_EFFEKSEER
#endif

	Effect::EffectMgr::Destroy();

	SoundMgr::Destroy();
	DungeonMgr::Destory();
	ComRes::Destory();
	ClickInput::Destroy();

	Delete(mSceneMgr);
	Delete(mFPS);
#ifdef __MY_DEBUG__
	Delete(mDebug);
#endif

}

void GameMgr::Initialize(){
	
	
	mSceneMgr->Initialize();

#ifdef __MY_DEBUG__
	mDebug->Initialize();
#endif

#ifdef __MY_WINDOWS__
	Keyboard_Initialize();
	//Mouse_Initialize();
#endif

	AppData::Create();

	MonsterMgr::Create();

}

void GameMgr::Finalize(){
	
#ifdef __MY_WINDOWS__
#ifdef ENABLE_EFFEKSEER
	EffekseerEffect::Effect::Destroy();
#endif // ENABLE_EFFEKSEER
#endif

	TaskMgr::getInstance().Finalize();
	mSceneMgr->Finalize();

#ifdef __MY_DEBUG__
	mDebug->Finalize();
#endif

#ifdef __MY_WINDOWS__
	Keyboard_Finalize();
	//Mouse_Finalize();
#endif

	MonsterMgr::Destory();

	AppData::Destory();

}

void GameMgr::PreviousUpdate() {
	mSceneMgr->PreviousUpdate();
	TaskMgr::getInstance().PreviousUpdate();
}

void GameMgr::InputUpdate() {
	
#ifdef __MY_WINDOWS__
	Keyboard_Updata();
	//Mouse_Updata();
#else
	//Touch_Updata();
#endif

	ClickInput::GetInstance()->Update();

	TaskMgr::getInstance().InputUpdate();


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

	MonsterMgr::Instance()->Updata();

	mSceneMgr->Updata();
	
	Effect::EffectMgr::GetInstance()->Update();
	
	TaskMgr::getInstance().Updata();
	SoundMgr::GetInstance()->Updata();
	
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
	mSceneMgr->PostUpdate();
	TaskMgr::getInstance().LateUpdata();

	mFPS->Wait();
}