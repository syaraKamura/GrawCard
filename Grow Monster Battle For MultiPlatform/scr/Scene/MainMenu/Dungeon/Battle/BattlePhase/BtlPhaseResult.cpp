/*
				ファイル名		:BtlPhaseResult.cpp
				作成者			:
				作成日時		:2019/06/29
				ソース説明		:
				
				
				備考
				
				
				
!*/
#include "Common/GameCommon.h"
#include "BtlPhaseResult.h"


namespace battle {
	
	bool BtlPhaseResult::Updata() {

		mStatus.Update();
		eState state = (eState)mStatus.GetState();
		switch (state) {
		case eState_Check:	_StateCheck();		break;
		case eState_Succeed:_StateSucceed();	break;
		case eState_Failed: _StateFailed();		break;
		default: break;
		}

		if (mStatus.IsEnd(eState_End)) {
			this->RequestKill();
		}
		return true;
	}


	// 状態を確認する
	void BtlPhaseResult::_StateCheck() {

		if (mStatus.IsFirstState()) {

		}
		
		if (BtlGetInfo().GetBattleResult() == eBattleResult_Win) {
			mStatus.SetState(eState_Succeed);
		}
		else {
			mStatus.SetState(eState_Failed);
		}

	}

	// 成功
	void BtlPhaseResult::_StateSucceed() {

		if (mStatus.IsFirstState()) {

		}
		
		mStatus.SetState(eState_End);

	}

	// 失敗
	void BtlPhaseResult::_StateFailed() {

		if (mStatus.IsFirstState()) {

		}

		mStatus.SetState(eState_End);

	}
	
}