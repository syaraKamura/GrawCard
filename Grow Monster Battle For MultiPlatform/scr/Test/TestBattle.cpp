/*
				ファイル名		:TestBase.cpp
				作成者			:
				作成日時		:2018/03/15
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "Scene/ISceneBase.h"
#include "TestBattle.h"
#include "Scene/MainMenu/Dungeon/Battle/BattleBase.h"
#include "AppData/AppData.h"

#ifdef __MY_DEBUG__

TestBattle::TestBattle(ISceneBase* changer) : SceneBase(changer) {
	mBattle = new BattleBase();
	TaskMgr::getInstance().Add(mBattle);
}

TestBattle::~TestBattle() {
	
}

bool TestBattle::Initialize() {

	AppData::GetInstance()->Load();

	return true;
}

void TestBattle::Finalize() {
	TaskMgr::getInstance().RequestKill(mBattle->GetTaskId());
	mBattle = NULL;
}

void TestBattle::PreviousUpdate() {
	
}

bool TestBattle::Updata() {

#ifdef __WINDOWS__
	if (Keyboard_Press(KEY_INPUT_X)) {
		dbg_ChangeScene_TestMenu();
	}
#endif

	return true;
}

void TestBattle::Draw() {
	
}

void TestBattle::PostUpdate() {
	
}

#endif //__MY_DEBUG__
