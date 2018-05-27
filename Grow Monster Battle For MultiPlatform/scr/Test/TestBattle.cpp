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
}

TestBattle::~TestBattle() {
	Delete(mBattle);
}

bool TestBattle::Initialize() {

	AppData::GetInstance().Load();

	return mBattle->Initialize();
}

void TestBattle::Finalize() {
	mBattle->Finalize();
}

void TestBattle::PreviousUpdate() {
	mBattle->PreviousUpdate();
}

bool TestBattle::Updata() {

#ifdef __WINDOWS__
	if (Keyboard_Press(KEY_INPUT_X)) {
		dbg_ChangeScene_TestMenu();
	}
#endif

	return mBattle->Updata();
}

void TestBattle::Draw() {
	mBattle->Draw();
}

void TestBattle::PostUpdate() {
	mBattle->PostUpdate();
}

#endif //__MY_DEBUG__
