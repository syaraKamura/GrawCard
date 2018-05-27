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

class BattleBase;

class TestBattle: public SceneBase {

private:
	BattleBase* mBattle;
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