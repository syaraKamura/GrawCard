/*
				ファイル名		:BattleProcCommand.cpp
				作成者			:
				作成日時		:2019/09/08
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "BattleProcCommand.h"


namespace battle {

	bool BattleProcCommand::Updata() {

		mStatus.Update();
		eState state = (eState)mStatus.GetState();
		switch (state)
		{
		case sState_Check:
			_StateCheck();
			break;
		case eState_AutoTarget:
			_StateAutoTarget();
			break;
		case eState_SelectTarget:
			_StateSelectTarget();
			break;
		default:
			break;
		}

		if (mStatus.IsEnd(eState_End)) {
			this->RequestKill();
		}
		return true;
	}

	void BattleProcCommand::Draw() {}


	// 行動タイプを確認
	void BattleProcCommand::_StateCheck() {

		if (mMoveMonster->GetSide() == eSide::eSide_Player) {
			mStatus.SetState(eState_AutoTarget);
		}
		else {
			mStatus.SetState(eState_AutoTarget);
		}

	}

	// 自動選択
	void BattleProcCommand::_StateAutoTarget() {

		std::vector<MonsterUnit*> targetList{};
		if (mMoveMonster->GetSide() == eSide_Enemy) {
			targetList = BtlGetInfo().GetPlayerMonsterList();
		}
		else {
			targetList = BtlGetInfo().GetEnmeyMonsterList();
		}
		
		int min = INT_MAX;
		MonsterUnit* AttackTarget = nullptr;
		for (auto& target : targetList) {
			if (target->IsDead()) { continue; }
			if (target->GetHp() < min) {
				min = target->GetHp();
				AttackTarget = target;
			}
		}
		BtlGetInfo().GetMoveData().Deffender = AttackTarget;
		BtlGetInfo().GetMoveData().AttackKind = eActiveType_Attack;
		
		

		mStatus.SetState(eState_End);
	}

	// ユーザー選択
	void BattleProcCommand::_StateSelectTarget() {

		mStatus.SetState(eState_End);
	}

}
