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
TestADV::TestADV(ISceneBase* changer) : SceneBase(changer){

	
}

bool TestADV::Initialize() {
	
	ScriptBase* add = new ScriptBase("ADV_0001.txt");

	mTaskId = TaskMgr::getInstance().Add(add, 1);

	return true;
}

void TestADV::Finalize() {

	TaskMgr::getInstance().RequestKill(mTaskId);

}

void TestADV::PreviousUpdate() {

	if (mTaskId != -1) {
		ScriptBase* task = dynamic_cast<ScriptBase*>(TaskMgr::getInstance().GetTask(mTaskId));
		if (task == NULL) return;
		if (task->IsEnd() == true) {
			TaskMgr::getInstance().RequestKill(mTaskId);
			mTaskId = -1;
			mNextScene->SceneChange(ISceneBase::eScene_TestMenu);
		}
	}

}

bool TestADV::Updata() {

#ifdef __WINDOWS__
	//テストメニューへ戻る
	if (Keyboard_Press(KEY_INPUT_X)) {
		mNextScene->SceneChange(ISceneBase::eScene_TestMenu);
		return true;
	}
#endif

	return true;
}

void TestADV::Draw() {

}

void TestADV::PostUpdate() {

}

#endif //__MY_DEBUG__