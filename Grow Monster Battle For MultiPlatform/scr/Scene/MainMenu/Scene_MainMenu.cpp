﻿/*
				ファイル名		:MainMenu.cpp
				作成者			:
				作成日時		:2017/12/23
				ソース説明		:メインメニュー
				
				
				備考
				
				
				
!*/

//	------- インクルード宣言

#include "Common/GameCommon.h"
#include "../ISceneBase.h"

#include "Scene_MainMenu.h"

Scene_MainMenu::Scene_MainMenu(ISceneBase* changer) : SceneBase(changer) {

}

void Scene_MainMenu::Initialize() {

	mState = eState_Initialize;
	mMenu = eMenu_MainMenu;
	mNextMenu = eMenu_None;

}

void Scene_MainMenu::Finalize() {

}

bool Scene_MainMenu::Updata() {

	switch (mState) {
	case eState_Initialize:
		NexetState(eState_Main, eFadeType_In, 30);
		break;
	case eState_Fade:
		if (Fade::GetInstance()->IsFadeEnd() == false) return true;

		mState = mNextState;
		mNextState = eState_None;

		break;
	case eState_Main:
		UpdataProc();
		break;
	case eState_Exit:
		mNextScene->SceneChange(ISceneBase::eScene_MainMenu);
		break;
	case eState_ExitDone:
		break;
	}

	return true;
}

void Scene_MainMenu::Draw() {

	if (mState < eState_Fade) return;

	switch (mMenu) {
	case eMenu_MainMenu:

		break;
	case eMenu_Quest:

		break;
	case eMenu_PlayerStatus:

		break;
	case eMenu_Monster:

		break;
	case eMenu_Gatya:

		break;
	case eMenu_Shop:

		break;
	default:
		Debug::LogPrintf("不正な値です。(%d)", (int)mMenu);
		break;
	}

}

bool Scene_MainMenu::UpdataProc() {

	if (mNextMenu != eMenu_None) {
		mMenu = mNextMenu;
		mNextMenu = eMenu_None;
	}

	switch (mMenu) {
	case eMenu_MainMenu:

		break;
	case eMenu_Quest:

		break;
	case eMenu_PlayerStatus:

		break;
	case eMenu_Monster:

		break;
	case eMenu_Gatya:

		break;
	case eMenu_Shop:

		break;
	default:
		Debug::LogPrintf("不正な値です。(%d)",(int)mMenu);
		break;
	}


#ifdef __WINDOWS__

#ifdef __MY_DEBUG__
	if (Keyboard_Press(KEY_INPUT_X)) {
		dbg_ChangeScene_TestMenu();
	}

#endif
#else

#endif

	return true;
}

void Scene_MainMenu::NexetState(eState nextState, eFadeType type, int fadeFrame) {

	mState = eState_Fade;
	mNextState = nextState;

	if (type == eFadeType_In) {
		Fade::GetInstance()->FadeIn(fadeFrame);
	}
	else if (type == eFadeType_Out) {
		Fade::GetInstance()->FadeOut(fadeFrame);
	}

}