/*
				ファイル名		:BtlPhaseMain.cpp
				作成者			:
				作成日時		:2019/06/29
				ソース説明		:
				
				
				備考
				
				
				
!*/
#include "Common/GameCommon.h"
#include "BattleProc/BattleProcCommand.h"
#include "../BattleCalculator.h"
#include "../BattleEffect.inc"

#include "BtlPhaseMain.h"


namespace battle {

	bool BtlPhaseMain::Updata() {

		mStatus.Update();
		eState state = (eState)mStatus.GetState();
		switch (state) {
		case eState_MoveOrder	: _StateMoveOrder(); break;
		case eState_Command		: _StateCommand(); break;
		case eState_Battle		: _StateBattle(); break;
		case eState_CheckTiming	: _StateCheckTiming(); break;
		default:break;
		}

		if (mStatus.IsEnd(eState_End)) {
			this->RequestKill();
		}
		return true;
	}

	void BtlPhaseMain::Draw() {}

	void BtlPhaseMain::_StateMoveOrder() {

		// 行動順番リスト作成
		mMoveList.clear();
		mNextMove = 0;

		std::vector<MonsterUnit*> data = BtlGetInfo().GetMonsterList();

		// 行動順番を設定
		for (unsigned int i = 0; i < data.size(); i++) {
			for (unsigned int j = 0; j < data.size(); j++) {
				MonsterUnit* mon1 = data[i];
				MonsterUnit* mon2 = data[j];
				if (mon1->GetSpeed() > mon2->GetSpeed()) {
					auto tmp = data[i];
					data[i] = data[j];
					data[j] = tmp;
				}

			}
		}

		for (auto& target : data) {
			for (int i = 0; i < BtlGetInfo().GetMonsterList().size(); i++) {
				MonsterUnit* unit = BtlGetInfo().GetMonsterList()[i];
				if (target == unit) {
					mMoveList.push_back(i);
					break;
				}
			}
		}
		
		mStatus.SetState(eState_Command);
	}

	void BtlPhaseMain::_StateCommand() {

		if (mStatus.IsFirstState()) {

			BtlGetInfo().ClearData();

			// 全て行動した
			if (mNextMove >= mMoveList.size()) {
				mStatus.SetState(eState_MoveOrder);
				return;
			}
			
			// 行動を選択する
			int move = mMoveList[mNextMove];
			mAttacker = BtlGetInfo().GetMonsterList()[move];
			mChildTaskId = _BtlAddTask(new BattleProcCommand(mAttacker));
		}





		if (_CheckTaskEnd(mChildTaskId)) {

			mStatus.SetState(eState_Battle);
		}

	}
	
	static Effect::EffectPlayData* pEft = nullptr;
	void BtlPhaseMain::_StateBattle() {

		if (mStatus.IsFirstState()) {

#if 0
			int size = BtlGetInfo().GetMonsterList().size();

			int target = GetRand(size);
			if (target >= size) {
				target = size - 1;
			}

			MonsterUnit* pUnit = BtlGetInfo().GetMonsterList()[target];

			pUnit->SubHp( 10 );
#endif

			MonsterUnit* Attacker = BtlGetInfo().GetMoveData().Attacker;
			MonsterUnit* Deffender = BtlGetInfo().GetMoveData().Deffender;
			Graphics& Graph = Deffender->GetGraphics();
			pEft = BtlGetMgr()->GetEffect().Play(eBattleEffect_FireClaw, Graph.GetPositionX(), Graph.GetPositionY());
			
			int damage = battle::BattleCalculator::NormalDamage(*Attacker->GetMonster(), *Deffender->GetMonster());
			Deffender->SubHp(damage);


		}
		
		if (_CheckTaskEnd(mChildTaskId) && pEft->isPlay == false) {
			mStatus.SetState(eState_CheckTiming);
		}

	}

	void BtlPhaseMain::_StateCheckTiming() {

		// 生存状態を確認

		bool IsAllDead = false;

		if (BtlGetInfo().AllDeadMonster(eSide_Player)) {
			IsAllDead = true;
		}
		if (BtlGetInfo().AllDeadMonster(eSide_Enemy)) {
			IsAllDead = true;
		}
		
		
		if (IsAllDead == false) {
			NextMove();
			mStatus.SetState(eState_Command);
		}
		else {
			mStatus.SetState(eState_End);
		}
		
	}

	//==================================================
	// private
	//==================================================

	// 次に行動するモンスター
	void BtlPhaseMain::NextMove() {
		mNextMove++;
		if (mNextMove >= mMoveList.size()) {
			return;
		}
		int move = mMoveList[mNextMove];
		mAttacker = BtlGetInfo().GetMonsterList()[move];
		if (mAttacker->IsDead()) {
			NextMove();
		}


	}

} // battle