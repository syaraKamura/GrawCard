/*
				ファイル名		:TestMosnterBox.h
				作成者			:
				作成日時		:2019/04/30
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __TEST_MONSTER_BOX_H__
#define __TEST_MONSTER_BOX_H__

#ifdef __MY_DEBUG__

#include "Scene/SceneBase.h"

namespace monsterBox {
	class MonsterBox;
};

class TestMonsterBox : public SceneBase {

private :
	
	monsterBox::MonsterBox* mMonsterBox;

public :

	TestMonsterBox(ISceneBase* changer);
	~TestMonsterBox();

	bool Initialize() override;
	void Finalize() override;
	void PreviousUpdate()override;
	bool Updata()override;
	void Draw() override;
	void PostUpdate() override;

};

#endif 
#endif // __TEST_MONSTER_BOX_H__