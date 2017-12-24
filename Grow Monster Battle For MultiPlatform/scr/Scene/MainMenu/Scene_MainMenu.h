/*
				ファイル名		:MainMenu.h
				作成者			:
				作成日時		:2017/12/23
				ソース説明		:メインメニュー
				
				
				備考
				
				
				
!*/

#ifndef __MAIN_MENU_H__
#define __MAIN_MENU_H__

#include "../SceneBase.h"

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

	eState mState;
	eState mNextState;

private:

	void NexetState(eState nextState, eFadeType type = eFadeType_None, int fadeFrame = 60);
	bool UpdataProc();

public :

	Scene_MainMenu(ISceneBase* changer);

	void Initialize() override;
	void Finalize() override;
	bool Updata() override;
	void Draw() override;

};

#endif // __MAIN_MENU_H__