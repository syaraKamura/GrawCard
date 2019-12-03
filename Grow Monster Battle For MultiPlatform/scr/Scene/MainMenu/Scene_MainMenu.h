/*
				ファイル名		:MainMenu.h
				作成者			:
				作成日時		:2017/12/23
				ソース説明		:メインメニュー
				
				
				備考
				
				
				
!*/

#ifndef __SCENE_MAIN_MENU_H__
#define __SCENE_MAIN_MENU_H__

#include "../SceneBase.h"
#include "Common/Debug/DebugList.h"

class Button;

class Scene_MainMenu : public SceneBase {

private :
	
	enum eState {
		eState_Initialize,
		eState_Fade,
		eState_Main,
		eState_Exit,
		eState_ExitDone,
		eState_None,
	};

	enum eFadeType {
		eFadeType_In,
		eFadeType_Out,
		eFadeType_None,
	};

	enum eMenu {
		eMenu_OpenRouge,
		eMenu_MainMenu,
		eMenu_Fade,
		eMenu_Quest,
		eMenu_PlayerStatus,
		eMenu_Monster,
		eMenu_Gatya,
		eMenu_Shop,

		eMenu_None,

	};

	enum eButton {
		eButton_Dungeon,
		eButton_MonsterBox,
		eButton_Player,
		eButton_Shop,
		eButton_Gatya,
		eButton_Num,
	};

	eState mState;
	eState mNextState;

	eMenu mMenu;
	eMenu mNextMenu;

	Button* mButtons[eButton_Num];

	int mBackImageOrder;
	int mButtonImageOrder;

	int mNowMenuTaskID;

	bool mIsEnableGraph;	//画像が非表示か？

	unsigned int mIsEndOpenRouge;

private:

	void NexetState(eState nextState, eFadeType type = eFadeType_None, float fadeFrame = 1.0f);
	bool UpdataProc();
	bool MainMenuProc();
	void MainMenuDraw();

public :

	Scene_MainMenu(ISceneBase* changer);
#ifdef __MY_DEBUG__
	Scene_MainMenu(ISceneBase* changer,Debug* debug);
#endif	//__MY_DEBUG__
	bool Initialize() override;
	void Finalize() override;
	bool Updata() override;
	void Draw() override;

	void OnClick(View* viewe) override;

#ifdef __MY_DEBUG__

public :

	class dbgScene_MainMenu : public DebugList {

	private:

		enum eList {
			eList_,
			eList_Num,
		};

	private:

		

	public :

		dbgScene_MainMenu();
		~dbgScene_MainMenu() override;

		void Execute() override;
		


	};

#endif

};

#endif // __SCENE_MAIN_MENU_H__