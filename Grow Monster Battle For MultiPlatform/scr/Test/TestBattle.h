/*
				ファイル名		:TestBattle.h
				作成者			:
				作成日時		:2018/03/15
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __TEST_BATTLE_H__
#define __TEST_BATTLE_H__

#ifdef __MY_DEBUG__

#include "Scene/SceneBase.h"

namespace battle {
	class BattleBase;
}

class TestBattle: public SceneBase {

private:

	enum eState {
		eState_SelectMenu,
		eState_DeckEdit,
		eState_MonsterList,
		eState_BattleStart,
		eState_BattleEnd,
	};

	enum eDeckEditState {
		eDeckEditState_DeckSelect,
		eDeckEditState_MonsterSelect,
	};

	typedef struct {
		char menuName[1024];
		eState state;
	}SELECT_DATA_s;

	static const SELECT_DATA_s SELECT_DATA_TBL[eState_BattleStart];

	eState mState;
	eDeckEditState mDeckEditState;

	int mSelectMenu;
	int mSelectMonster;
	int mSelectDeckNum;

	battle::BattleBase* mBattle;
	Player* mPlayer;
	SaveData* mSaveData;
public :

	TestBattle(ISceneBase* changer);
	~TestBattle();
	
	bool Initialize() override;
	void Finalize() override;
	void PreviousUpdate()override;
	bool Updata()override;
	void Draw() override;
	void PostUpdate() override;

};

#endif//__MY_DEBUG__

#endif // __TEST_BATTLE_H__