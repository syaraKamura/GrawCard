/*
				ファイル名		:DungeonMenu.h
				作成者			:
				作成日時		:2018/03/12
				ソース説明		:
				 
					ダンジョンメニュー
				
				備考
				
				
				
!*/

#ifndef __DUNGEON_MENU_H__
#define __DUNGEON_MENU_H__

#include "Common/Task/TaskBase.h"

class DungeonMenu : public TaskBase {

private:

	enum eState {
		eState_None = -1,
		eState_SelectMode,
		eState_SelectStoryMap,
		eState_SelectQuestMap,
		eState_SelectDungeonMap,
		eState_Adventure,
		eState_Fade,
		eState_Exit,
		eState_ExitDone,
	};

	enum eMenu {
		eMenu_None = -1,
		eMenu_Story,		//ストーリー
		eMenu_Quest,		//クエスト
		eMenu_Dungeon,		//ダンジョン
		eMenu_Num,
	};

	enum eFade {
		eFade_None,
		eFade_In,
		eFade_Out,
	};

	char NAME_LIST[eMenu_Num][256] = {
		{"ストーリー"},
		{"クエスト"},
		{"ダンジョン"},
	};
	
#if 0
	typedef struct {
		int mID;
		int mQuestType;
		int mQuestNo;
	};

	typedef struct {
		int mMosterTblNo;
		int mBeforeAdvNo;
		int mAfterAdvNo;
	};
#endif 

private:
	
	int mSelect;
	int mBackImageOrder;
	
	int mStroySelectNum;
	
	eState mState;
	eState mNextState;
	eState mOldState;

	int mTaskId;
	
	/*
		ステート切り替え
	*/
	void ChangeState(eState next,eFade fade,int fadeTime = 30);

	

public :

	DungeonMenu();
	~DungeonMenu();

	bool Initialize()override;
	void Finalize()override;

	void PreviousUpdate()override;
	bool Updata()override;
	void Draw()override;
	void PostUpdate() override;
	
	void OnClick(View* view) override;

};

#endif // __DUNGEON_MENU_H__