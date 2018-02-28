/*
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

#ifdef __MY_DEBUG__
	
#endif //__MY_DEBUG__

}

#ifdef __MY_DEBUG__
Scene_MainMenu::Scene_MainMenu(ISceneBase* changer, Debug* debug) : SceneBase(changer, debug) {

}
#endif

bool Scene_MainMenu::Initialize() {

	mState = eState_Initialize;
	mMenu = eMenu_MainMenu;
	mNextMenu = eMenu_None;

	Graphics* add = ComRes::Instance()->GetGraphicHandle(ComRes::eComResName_MainMenuBG);
	add->SetPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	mBackImageOrder = GraphicsDrawMgr::GetInstance()->Add(add, 0);

	GraphicsMulti* multiAdd = new GraphicsMulti();
	multiAdd->Load("Resources/Graphics/UI/button/menu_adventure2.png", 160, 600);
	multiAdd->Load("Resources/Graphics/UI/button/menu_monster2.png", 280, 600);
	multiAdd->Load("Resources/Graphics/UI/button/menu_player2.png", 400, 600);
	multiAdd->Load("Resources/Graphics/UI/button/menu_shop2.png", 520, 600);
	multiAdd->Load("Resources/Graphics/UI/button/menu_gacha2.png", 640, 600);
	mButtonImageOrder = GraphicsDrawMgr::GetInstance()->Add(multiAdd, 1);
	
#ifdef __MY_DEBUG__
	if (mDebug != NULL) {
		mDebug->SetDebugList((DebugList*)new dbgScene_MainMenu());
	}
#endif

	return true;
}

void Scene_MainMenu::Finalize() {
	GraphicsDrawMgr::GetInstance()->Remove(mBackImageOrder);
	GraphicsDrawMgr::GetInstance()->ReleseRequest(mButtonImageOrder);

#ifdef __MY_DEBUG__
	mDebug->DeleteList();
#endif	//__MY_DEBUG__

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
		MainMenuDraw();
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

	bool result = true;

	switch (mMenu) {
	case eMenu_MainMenu:
		result = MainMenuProc();
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

	return result;
}

bool Scene_MainMenu::MainMenuProc() {

	return true;
}

void Scene_MainMenu::MainMenuDraw() {

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


#ifdef __MY_DEBUG__

Scene_MainMenu::dbgScene_MainMenu::dbgScene_MainMenu() : DebugList()
{
	AddList(eList_,"テスト項目1", DebugList::eDebugType_Flag, false);
}

Scene_MainMenu::dbgScene_MainMenu::~dbgScene_MainMenu() {
	
}

void Scene_MainMenu::dbgScene_MainMenu::Execute(){
	
	switch (mListSelect) {
	case eList_:
		Debug::ErorrMessage("テスト項目選択!");
		break;
	default:

		break;
	}

}

#endif