/*
				ファイル名		:TestADV.cpp
				作成者			:
				作成日時		:2018/06/14
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "Scene/ISceneBase.h"
#include "Common/Script/ScriptBase.h"
#include "TestADV.h"


#ifdef __MY_DEBUG__

typedef struct {
	char mAdvTitle[128];
	char mFileName[128];
}ADV_TBL_t;

static ADV_TBL_t ADV_TBL_DATA[] = 
{
	// 題名		ファイル名
	{ "TEST"	,"ADV_0001.txt" },
	{ "はじまり","ADV_0000.txt" },
	{ " ―異世界からの訪問者―","ADV_0003.txt" },
};

TestADV::TestADV(ISceneBase* changer) : SceneBase(changer){

	
}

bool TestADV::Initialize() {
	
	mTaskId = -1;
	mSelect = 0;
	return true;

}

void TestADV::Finalize() {

	TaskMgr::getInstance().RequestKill(mTaskId);

}

void TestADV::PreviousUpdate() {

	if (mTaskId != -1) {
		AdvScript::ScriptBase* task = dynamic_cast<AdvScript::ScriptBase*>(TaskMgr::getInstance().GetTask(mTaskId));
		if (task == NULL) return;
		if (task->IsEnd() == true) {
			TaskMgr::getInstance().RequestKill(mTaskId);
			mTaskId = -1;
		}
	}

}

bool TestADV::Updata() {

#ifdef __WINDOWS__
	if (mTaskId == -1) {
		
		if (Keyboard_Press(KEY_INPUT_DOWN)) {
			mSelect = (mSelect + 1) % ArrySize(ADV_TBL_DATA);
		}
		else if (Keyboard_Press(KEY_INPUT_UP)) {
			mSelect = (mSelect + (ArrySize(ADV_TBL_DATA) - 1)) % ArrySize(ADV_TBL_DATA);
		}

		if (Keyboard_Press(KEY_INPUT_Z)) {
			AdvScript::ScriptBase* add = new AdvScript::ScriptBase(ADV_TBL_DATA[mSelect].mFileName);
			mTaskId = TaskMgr::getInstance().Add(add, 1);
		}

	}



	//テストメニューへ戻る
	if (Keyboard_Press(KEY_INPUT_X)) {
		mNextScene->SceneChange(ISceneBase::eScene_TestMenu);
		return true;
	}
#endif

	return true;
}

void TestADV::Draw() {

	if (mTaskId != -1)  return;

	DrawString(20, 40, "テストアドベンチャー", GetColor(255, 255, 255));

	for (int i = 0; i < ArrySize(ADV_TBL_DATA); i++) {
		ADV_TBL_t data = ADV_TBL_DATA[i];

		int y = 80 + i * 20;
		if (mSelect == i) {
			DrawFormatString(20, y, GetColor(255, 0, 0), "%s", data.mAdvTitle);
		}
		else {
			DrawFormatString(20, y, GetColor(255, 255, 255), "%s", data.mAdvTitle);
		}

	}

}

void TestADV::PostUpdate() {

}

#endif //__MY_DEBUG__