/*
				ファイル名		:BtlPhaseStart.cpp
				作成者			:
				作成日時		:2019/06/29
				ソース説明		:
				
				
				備考
				
				
				
!*/
#include "Common/GameCommon.h"

#include "../BattleUtil/BtlCommon.h"

#include "../BattleBase.h"
#include "../BattleAnimation.h"

#include "BtlPhaseStart.h"


namespace battle {

	using namespace anim;

	bool BtlPhaseStart::Updata() {

		mStatus.Update();
		eState state = (eState)mStatus.GetState();
		switch (state) {
			case eState_Start: _StateInit();  break;
		}
		if (mStatus.IsEnd(eState_Exit)) {
			this->RequestKill();
		}
		return true;
	}

	void BtlPhaseStart::_StateInit() {
		
		if (mStatus.IsFirstState()) {
			mAnimPlayMonsterNum = 0;
			mStartAnimCount = 0;
			for (unsigned int i = 0; i < BtlGetInfo().GetMonsterList().size(); i++) {
				MonsterUnit* unit = BtlGetInfo().GetMonsterList()[i];
				if (unit->GetSide() == eSide_Enemy ) {
					BtlGetAnim().RequestAnim(BattleAnimation::eAnimationNo_Transrate_Scale_01, &unit->GetGraphics(), true);
					unit->GetGraphics().SetVisible(true);
					unit->GetGraphics().SetScale(0.0);
				}
				else {
					mPlayerMonsterList.push_back(i);
				}
			}

		}
		
		mStartAnimCount++;

		if (mStartAnimCount % 20 != 0) return;

		if (mAnimPlayMonsterNum >= mPlayerMonsterList.size()) {
			mStatus.SetState(eState_Exit);
			mAnimPlayMonsterNum = 0;
			mStartAnimCount = 0;
			return;
		}
		
		int monsterNum = mPlayerMonsterList[mAnimPlayMonsterNum];
		MonsterUnit* monster = BtlGetInfo().GetMonsterList()[monsterNum];

		BattleAnimation::eAnimationNo animNo = BattleAnimation::eAnimationNo_InSide_00;
		if (monster->GetHomePosition() == Monster::eHomePosition_Back) {
			animNo = BattleAnimation::eAnimationNo_InSide_02;
		}

		//mBattleAnimation->RequestAnim(animNo, &mPlayerCard[mAnimPlayMonsterNum], true);
		BtlGetAnim().RequestAnim(animNo, &monster->GetGraphics(), true);
		monster->GetGraphics().SetVisible(true);
		monster->GetGraphics().SetAlpha(0);
		mAnimPlayMonsterNum++;
		
	}


}	// battle