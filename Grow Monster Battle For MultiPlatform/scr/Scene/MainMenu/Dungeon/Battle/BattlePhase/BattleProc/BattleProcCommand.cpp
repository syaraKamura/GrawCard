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
		case sState_Check:			_StateCheck();			break;
		case eState_AutoTarget:		_StateAutoTarget();		break;
		case eState_SelectCommand:	_StateSelectCommand();	break;
		case eState_SelectTarget:	_StateSelectTarget();	break;
		default:											break;
		}

		//
		if (mStatus.IsEnd(eState_End)) {
			//this->RequestKill();
			return false;
		}
		return true;
	}

	void BattleProcCommand::Draw() {}


	// 行動タイプを確認
	void BattleProcCommand::_StateCheck() {

		if (mMoveMonster->GetSide() == eSide::eSide_Player) {
			switch (BtlGetInfo().GetPlayMode()) {
			case ePlayMode_Input:
				mStatus.SetState(eState_SelectCommand);
				break;
			case ePlayMode_Auto:
				mStatus.SetState(eState_AutoTarget);
				break;
			}
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

	// コマンド選択
	void BattleProcCommand::_StateSelectCommand() {
		if (mStatus.IsFirstState()) {
			int posX = mMoveMonster->GetGraphics().GetPositionX();
			int posY = mMoveMonster->GetGraphics().GetPositionY();
			BtlGetUIMgr().GetCmdUI().Open(posX, posY);
		}

		if (BtlGetInfo().CheckPlayMode(ePlayMode_Auto)) {
			BtlGetUIMgr().GetCmdUI().Close();
			mStatus.SetState(eState_AutoTarget);
		}

		if (BtlGetUIMgr().GetCmdUI().IsVisible()) {
			return;
		}

		// とりあえず自動選択を行う
		_StateAutoTarget();

		BtlGetInfo().GetMoveData().AttackKind = BtlGetUIMgr().GetCmdUI().GetValue();
		mStatus.SetState(eState_SelectTarget);
	}

	// ユーザー選択
	void BattleProcCommand::_StateSelectTarget() {

		if (mStatus.IsFirstState()) {
			
		}

		mStatus.SetState(eState_End);
	}

}
