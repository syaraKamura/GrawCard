/*
				ファイル名		:TestMapField.cpp
				作成者			:
				作成日時		:2018/12/23
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "Scene/ISceneBase.h"

#include "Scene/MainMenu/Dungeon/Map/MapField.h"

#include "TestMapField.h"


TestMapField::TestMapField(ISceneBase* changer) : SceneBase(changer){

	mMapField = new MapField(1);

}

TestMapField::~TestMapField() {
	Delete(mMapField);
}

bool TestMapField::Initialize() {

	return true;
}

void TestMapField::Finalize() {

}

void TestMapField::PreviousUpdate(){

}

bool TestMapField::Updata(){


	mMapField->Updata();

#ifdef __WINDOWS__
#ifdef __MY_DEBUG__
	if (mMapField->dbg_IsStateMain()) {
		if (Keyboard_Press(KEY_INPUT_X)) {

			dbg_ChangeScene_TestMenu();

		}
	}
#endif
#endif

	return true;
}

void TestMapField::Draw() {

	mMapField->Draw();

}

void TestMapField::PostUpdate() {

}
