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

	char NAME_LIST[eMenu_Num][256] = {
		{"ストーリー"},
		{"クエスト"},
		{"ダンジョン"},
	};
	
private:
	
	int mSelect;
	int mBackImageOrder;
	eState mState;

public :

	DungeonMenu();
	~DungeonMenu();

	bool Initialize()override;
	void Finalize()override;

	void PreviousUpdate()override;
	bool Updata()override;
	void Draw()override;
	void PostUpdate() override;
	

};

#endif // __DUNGEON_MENU_H__