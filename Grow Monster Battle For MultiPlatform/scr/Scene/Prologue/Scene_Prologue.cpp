/*
				ファイル名		:Scene_Prologue.cpp
				作成者			:
				作成日時		:2018/11/19
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "Scene/ISceneBase.h"

#include "Common/Script/ScriptBase.h"

#include "Scene_Prologue.h"


Scene_Prologue::Scene_Prologue(ISceneBase* changer) : SceneBase(changer){

}

#ifdef __MY_DEBUG__
Scene_Prologue::Scene_Prologue(ISceneBase* changer, Debug* debug) : SceneBase(changer) {

}
#endif	//__MY_DEBUG__

bool Scene_Prologue::Initialize() {

	Fade::GetInstance()->FadeIn();

	//mPrologue = new AdvScript::ScriptBase("ADV_0000.txt");
	mPrologue = ComRes::Instance()->StartAdvScript(0);
	this->GetTask().Add(mPrologue);

	return true;
}
void Scene_Prologue::Finalize() {
	this->GetTask().RequestKill(mPrologue->GetTaskId());

	SaveData* save = AppData::GetInstance()->GetSaveData();
	save->SetFlag(AppData::eAPPDATA_FLAG_DipsOpenRogue, true);
	AppData::GetInstance()->Save();

	mPrologue = NULL;
}

bool Scene_Prologue::Updata() {

	if (mPrologue->IsEnd()) {
		mNextScene->SceneChange(ISceneBase::eScene_MainMenu);
	}

#ifdef __MY_DEBUG__
#ifdef __WINDOWS__
	if (Keyboard_Press(KEY_INPUT_X)) {
		dbg_ChangeScene_TestMenu();
	}
#endif	// __WINDOWS__
#endif	// __MY_DEBUG__

	return true;
}

void Scene_Prologue::Draw() {

}

