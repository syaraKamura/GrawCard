/*
				ファイル名		:BtlInfo.cpp
				作成者			:
				作成日時		:2019/07/06
				ソース説明		:
				
				
				備考
				
				
				
!*/
#include "Common/GameCommon.h"
#include "BtlInfo.h"

namespace battle{

	BtlInfo::BtlInfo() {
		mTurn = 0;
		memset(mMonsterNum, 0, sizeof(int) * eSide_Max);
	}
	BtlInfo::~BtlInfo() {

		for (int i = 0; i < mMonsterList.size(); i++) {
			Delete(mMonsterList[i]);
		}
		mMonsterList.clear();

	}

	void BtlInfo::AddMonster(MonsterUnit* monster) {
		eSide side = monster->GetSide();
		mMonsterList.push_back(monster);
		mMonsterNum[side]++;
	}

	bool BtlInfo::AllDeadMonster(eSide side) {
		int deadNum = 0;
		for (auto& monster : GetMonsterList()) {
			if (monster->GetSide() != side) { continue;  }
			if (monster->IsDead()) {
				deadNum++;
			}
		}
		return (deadNum >= GetHaveMonsterNum(side));
	}

}


