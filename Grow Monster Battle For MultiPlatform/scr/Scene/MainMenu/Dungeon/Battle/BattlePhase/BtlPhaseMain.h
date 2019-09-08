/*
				ファイル名		:BtlPhaseMain.h
				作成者			:
				作成日時		:2019/06/29
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __BTL_PHASE_MAIN_H__
#define __BTL_PHASE_MAIN_H__

#include "BtlTaskBase.h"
#include <vector>
namespace battle {

	class BtlPhaseMain : public BtlTaskBase {

	private:

		enum eState {
			eState_MoveOrder,
			eState_Command,
			eState_Battle,
			eState_CheckTiming,

			eState_End,
		};

		int mChildTaskId;
		int mNextMove;
		std::vector<int> mMoveList;

		MonsterUnit* mAttacker{};		// 攻撃するモンスター
		MonsterUnit* mTarget{};		// 攻撃対象モンスター

	private:

		// 次に行動するモンスター
		void NextMove();

	public:

		BtlPhaseMain() :
			BtlTaskBase(),
			mChildTaskId(-1),
			mNextMove(0){}

		bool Updata() override;
		void Draw()override;

		
		//行動順番
		void _StateMoveOrder();
		//コマンド入力
		void _StateCommand();
		//バトル
		void _StateBattle();
		//生存チェック
		void _StateCheckTiming();

	};

}


#endif // __BTL_PHASE_MAIN_H__