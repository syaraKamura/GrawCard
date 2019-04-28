/*
				ファイル名		:MainMenu.cpp
				作成者			:
				作成日時		:2017/12/23
				ソース説明		:メインメニュー
				
				
				備考
				
				
				
!*/

//	------- インクルード宣言

#include "Common/GameCommon.h"
#include "Common/ResourceTable/GraphTable.h"
#include "../ISceneBase.h"
#include "Scene_MainMenu.h"
#include "Common/Graphics/Button/Button.h"
#include "Common/Graphics/Button/ButtonGraph.h"
#include "Common/Script/ScriptBase.h"
#include "Dungeon/DungeonMenu.h"
#include "PlayerInfomation/PlayerInfomation.h"

Scene_MainMenu::Scene_MainMenu(ISceneBase* changer) : SceneBase(changer) {

#ifdef __MY_DEBUG__
	
#endif //__MY_DEBUG__

}

#ifdef __MY_DEBUG__
Scene_MainMenu::Scene_MainMenu(ISceneBase* changer, Debug* debug) : SceneBase(changer, debug) {

}
#endif

bool Scene_MainMenu::Initialize() {

	//Graphics* add = ComRes::Instance()->GetGraphicHandle(ComRes::eComResName_MainMenuBG);
	Graphics* add = new Graphics();
	add->Initialize(graphicsTable::GetGraphTag(graphicsTable::eGraphTag_MainMenuBG));
	if (add != NULL) {
		add->SetPosition(0, 0);
		mBackImageOrder = GraphicsDrawMgr::GetInstance()->Add(add, 0);
	}
	else {
		//汎用リソースからグラフィックの取得失敗
		Debug::ErorrMessage("汎用リソースからグラフィックスの取得に失敗しました\n(ComRes::eComResName_MainMenuBG)\n");
		return false;
	}

#if true
	int x = 160;
	int y = 900;
	mButtons[Scene_MainMenu::eButton_Dungeon] = new Button("Resources/Graphics/UI/button/menu_adventure2.png", x, y, "");		
	x += 190;
	mButtons[Scene_MainMenu::eButton_MonsterBox] = new Button("Resources/Graphics/UI/button/menu_monster2.png", x, y, "");
	x += 190;
	mButtons[Scene_MainMenu::eButton_Player] = new Button("Resources/Graphics/UI/button/menu_player2.png", x, y, "");
	x += 190;
	mButtons[Scene_MainMenu::eButton_Shop] = new Button("Resources/Graphics/UI/button/menu_shop2.png", x, y, "");
	x += 190;
	mButtons[Scene_MainMenu::eButton_Gatya] = new Button("Resources/Graphics/UI/button/menu_gacha2.png", x, y, "");

	ButtonGraph* buttonGraph = new ButtonGraph();

	for (int i = 0; i < 5; i++) {
		mButtons[i]->SetOnListener(this);
		buttonGraph->AddButton(mButtons[i]);
	}

	mButtonImageOrder = GraphicsDrawMgr::GetInstance()->Add(buttonGraph, 1);

	SoundMgr::GetInstance()->Play("MainMenu", SoundMgr::ePlayType_Loop);


#else
	GraphicsMulti* multiAdd = new GraphicsMulti();
	multiAdd->Load("Resources/Graphics/UI/button/menu_adventure2.png", 160, 600);
	multiAdd->Load("Resources/Graphics/UI/button/menu_monster2.png", 280, 600);
	multiAdd->Load("Resources/Graphics/UI/button/menu_player2.png", 400, 600);
	multiAdd->Load("Resources/Graphics/UI/button/menu_shop2.png", 520, 600);
	multiAdd->Load("Resources/Graphics/UI/button/menu_gacha2.png", 640, 600);
	mButtonImageOrder = GraphicsDrawMgr::GetInstance()->Add(multiAdd, 1);
#endif

	mNowMenuTaskID = -1;
	mIsEnableGraph = false;
#ifdef __MY_DEBUG__
	if (mDebug != NULL) {
		//mDebug->SetDebugList((DebugList*)new dbgScene_MainMenu());
	}
#endif


	mState = eState_Initialize;

	SaveData* saveData = AppData::GetInstance()->GetSaveData();

	mIsEndOpenRouge = 0;

	if (saveData != NULL) {
		//mIsEndOpenRouge = saveData->GetFlag((int)AppData::eAPPDATA_FLAG_DipsOpenRogue);
		mIsEndOpenRouge = 1;//saveData->GetFlag((int)AppData::eAPPDATA_FLAG_DipsOpenRogue);
	}

	mMenu = eMenu_MainMenu;

	if (mIsEndOpenRouge == 0) {
		mMenu = eMenu_OpenRouge;
		GraphicsDrawMgr::GetInstance()->Get(mBackImageOrder)->SetVisible(false);
		GraphicsDrawMgr::GetInstance()->Get(mButtonImageOrder)->SetVisible(false);
	}

	mNextMenu = eMenu_None;

	return true;
}

void Scene_MainMenu::Finalize() {
	GraphicsDrawMgr::GetInstance()->Remove(mBackImageOrder);
	GraphicsDrawMgr::GetInstance()->ReleseRequest(mButtonImageOrder);

	SoundMgr::GetInstance()->Stop();

#ifdef __MY_DEBUG__
	//mDebug->DeleteList();
#endif	//__MY_DEBUG__

}

bool Scene_MainMenu::Updata() {

	switch ((int)mState) {
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

	if (mNowMenuTaskID != -1) return;

	if (mState < eState_Fade) return;

	switch ((int)mState) {
	case eMenu_MainMenu:
		MainMenuDraw();
		break;
	case eMenu_Fade:

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
		Debug::LogPrintf("mState は 不正な値です。(%d)", (int)mState);
		break;
	}

}

bool Scene_MainMenu::UpdataProc() {

	if (mNowMenuTaskID != -1) {

		if (mMenu == eMenu_OpenRouge) {
			TaskBase* task = TaskMgr::getInstance().GetTask(mNowMenuTaskID);
			AdvScript::ScriptBase* script = dynamic_cast<AdvScript::ScriptBase*>(task);
			if (script != NULL) {
				if (script->IsEnd()) {
#if true
					mIsEndOpenRouge = 1;
					TaskMgr::getInstance().RequestKill(mNowMenuTaskID);
#else
					SaveData* saveData = AppData::GetInstance().GetSaveData();
					if (saveData != NULL) {
						SaveData::FLAG_DATA_t* flag = saveData->GetFlagData();
						flag->mFlags[AppData::eAPPDATA_FLAG_DipsOpenRogue] = 1;
						AppData::GetInstance().Save();
					}
#endif
				}
			}
		}
		
		if (TaskMgr::getInstance().GetTask(mNowMenuTaskID) == NULL) {
			mNowMenuTaskID = -1;
			NexetState(eState_Main, eFadeType_In, 30);

			GraphicsBase* graph = GraphicsDrawMgr::GetInstance()->Get(mBackImageOrder);
			if (graph != NULL) {
				graph->SetVisible(true);
			}
			GraphicsBase* button = GraphicsDrawMgr::GetInstance()->Get(mButtonImageOrder);
			if (button != NULL) {
				button->SetVisible(true);
			}

		}
		else {
			if (Fade::GetInstance()->IsFadeEnd() && !mIsEnableGraph) {
				GraphicsBase* graph = GraphicsDrawMgr::GetInstance()->Get(mBackImageOrder);
				if (graph != NULL) {
					graph->SetVisible(false);
				}
				GraphicsBase* button = GraphicsDrawMgr::GetInstance()->Get(mButtonImageOrder);
				if (button != NULL) {
					button->SetVisible(false);
				}
				mIsEnableGraph = true;
			}
		}
		return true;		
	}

	if (Fade::GetInstance()->IsFadeEnd()) {
		//SaveData* saveData = AppData::GetInstance().GetSaveData();
		//if (saveData != NULL && saveData->GetFlag((int)AppData::eAPPDATA_FLAG_DipsOpenRogue) == 0) {
		if(mIsEndOpenRouge == 0){
			mMenu = eMenu_OpenRouge;
		}
		else {
			mMenu = eMenu_MainMenu;
			SoundMgr::GetInstance()->Play("MainMenu", SoundMgr::ePlayType_Loop);
		}
		
	}

	if (mNextMenu != eMenu_None) {
		mMenu = eMenu_Fade;
	}

	bool result = true;

	switch (mMenu) {
	case eMenu_OpenRouge:
	{
		mNowMenuTaskID = TaskMgr::getInstance().Add(new AdvScript::ScriptBase("ADV_0000.txt"), TaskMgr::ePriorty_0);
		mIsEnableGraph = false;
	}
		break;
	case eMenu_MainMenu:
		result = MainMenuProc();
		break;
	case eMenu_Fade:
		mMenu = mNextMenu;
		mNextMenu = eMenu_None;
		Fade::GetInstance()->FadeOut(30);
		break;
	case eMenu_Quest:
	{
		mNowMenuTaskID = TaskMgr::getInstance().Add(new DungeonMenu(), TaskMgr::ePriorty_0);
		mIsEnableGraph = false;
	}
		break;
	case eMenu_PlayerStatus:
	{
		mNowMenuTaskID = TaskMgr::getInstance().Add(new PlayerInfomation(), TaskMgr::ePriorty_0);
		mIsEnableGraph = false;
	}
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



	return result;
}

bool Scene_MainMenu::MainMenuProc() {

#ifdef __WINDOWS__

#ifdef __MY_DEBUG__
	if (Keyboard_Press(KEY_INPUT_X)) {
		dbg_ChangeScene_TestMenu();
	}
	if (Keyboard_Press(KEY_INPUT_Z)) {
		mNextMenu = eMenu_Quest;
	}
#endif
#endif

#if false
	auto mGraph = GraphicsDrawMgr::GetInstance()->Get(this->mButtonImageOrder);
	int selectNumber = -1;
	if (mGraph != NULL) {
		selectNumber = mGraph->TouchNumber();
	}
	if (selectNumber == 0) {
		//dbg_ChangeScene_TestMenu();
		mNextMenu = eMenu_Quest;
	}
	else if (selectNumber == 1) {
#ifdef __MY_DEBUG__
		//mNextScene->SceneChange(ISceneBase::eScene_AITest);
		mNextScene->SceneChange(ISceneBase::eScene_TestADV);
#endif // __MY_DEBUG__
	}
	else if (selectNumber == 2) {
		mNextMenu = eMenu_PlayerStatus;
	}
#endif


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

void Scene_MainMenu::OnClick(View* viewe) {

	if (viewe == mButtons[Scene_MainMenu::eButton_Dungeon]) {
		mNextMenu = eMenu_Quest;
	}
	else if (viewe == mButtons[Scene_MainMenu::eButton_MonsterBox]) {
#ifdef __MY_DEBUG__
		mNextScene->SceneChange(ISceneBase::eScene_TestADV);
#endif //__MY_DEBUG__
	}
	else if (viewe == mButtons[Scene_MainMenu::eButton_Player]) {
		mNextMenu = eMenu_PlayerStatus;
	}
	else if (viewe == mButtons[Scene_MainMenu::eButton_Shop]) {

	}
	else if (viewe == mButtons[Scene_MainMenu::eButton_Gatya]) {

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