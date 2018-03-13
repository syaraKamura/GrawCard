/*
				ファイル名		:DungeonMenu.cpp
				作成者			:
				作成日時		:2018/03/12
				ソース説明		:
				
				
				備考
				
				
				
!*/
#include "Common/GameCommon.h"
#include "DungeonMenu.h"

DungeonMenu::DungeonMenu() : TaskBase() {
	
}

DungeonMenu::~DungeonMenu() {

}

bool DungeonMenu::Initialize() {
	
	if (Fade::GetInstance()->IsFadeEnd() == false) return false;
	
	Graphics* add = ComRes::Instance()->GetGraphicHandle(ComRes::eComResName_CommonBG);
	add->SetPosition(0, 0);
	mBackImageOrder = GraphicsDrawMgr::GetInstance()->Add(add, 1);
	
	Fade::GetInstance()->FadeIn(30);
	
	mSelect = 0;
	mState = eState_None;

	return true;
}

void DungeonMenu::Finalize() {
	GraphicsDrawMgr::GetInstance()->Remove(this->mBackImageOrder);
	
}

void DungeonMenu::PreviousUpdate() {

}

bool DungeonMenu::Updata() {
	if (Fade::GetInstance()->IsFadeEnd() == false) return true;
	if (mState == eState_None) {

#ifdef __WINDOWS__
		if (Keyboard_Press(KEY_INPUT_DOWN)) {
			mSelect = (mSelect + 1) % eMenu_Num;
		}
		else if (Keyboard_Press(KEY_INPUT_UP)) {
			mSelect = (mSelect + (eMenu_Num - 1)) % eMenu_Num;
		}
		if (Keyboard_Press(KEY_INPUT_Z)) {

		}
		//とりあえず自身のタスクを削除する
		else if (Keyboard_Press(KEY_INPUT_X)) {
			mState = eState_Fade;
		}

#else

		//とりあえず自身のタスクを削除する
		if (Touch_Relese(0)) {
			mState = eState_Fade;
		}

#endif

	}

	switch (mState) {
	case eState_Fade:
		Fade::GetInstance()->FadeOut(30);
		mState = eState_Exit;
		break;
	case eState_Exit:
		if (Fade::GetInstance()->IsFadeEnd()) {
			mState = eState_ExitDone;
		}
		break;
	case eState_ExitDone:
		TaskMgr::getInstance().RequestKill(this->GetTaskId());
		break;
	}


	return true;
}

void DungeonMenu::Draw() {
	
	DrawString(170, 100 + 60 * mSelect,"■", GetColor(255, 0, 0));
	for (int i = 0; i < eMenu_Num; i++) {
		DrawString(200, 100 + 60 * i, NAME_LIST[i], GetColor(255, 0, 0));
	}

}

void DungeonMenu::PostUpdate() {

}
