/*
				ファイル名		:TestMonsterBox.cpp
				作成者			:
				作成日時		:2019/04/30
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "AppData/Character/Monster/MonsterBox.h"
#include "AppData/Character/Monster/MonsterMgr.h"
#include "Scene/ISceneBase.h"

#include "TestMonsterBox.h"

#ifdef __MY_DEBUG__

TestMonsterBox::TestMonsterBox(ISceneBase* changer) : SceneBase(changer){
	mMonsterBox = new monsterBox::MonsterBox();

	for (int i = 0; i < MonsterMgr::Instance()->GetMonsterNum(); i++) {
		mMonsterBox->Add(MonsterMgr::Instance()->GetMonsterData(i));
	}

}

TestMonsterBox::~TestMonsterBox() {

}

bool TestMonsterBox::Initialize() {

	return true;
}

void TestMonsterBox::Finalize() {

}

void TestMonsterBox::PreviousUpdate() {

}

bool TestMonsterBox::Updata() {
	
#ifdef __WINDOWS__
	if (Keyboard_Press(KEY_INPUT_X)) {
		dbg_ChangeScene_TestMenu();
	}
#endif

	mMonsterBox->Update();

	return true;
}

void TestMonsterBox::Draw() {
	mMonsterBox->Draw();
}

void TestMonsterBox::PostUpdate() {

}


#endif //__MY_DEBUG__