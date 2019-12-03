/*
				ファイル名		:BattleProcCommand.h
				作成者			:
				作成日時		:2019/09/08
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __BATTLE_PROC_COMMAND_H__
#define __BATTLE_PROC_COMMAND_H__

#include "../BtlTaskBase.h"

namespace battle {

	class BattleProcCommand : public BtlTaskBase{

	private:

		enum eState {

			sState_Check,			// 行動タイプを確認
			eState_AutoTarget,		// 自動選択
			eState_SelectCommand,	// コマンド選択
			eState_SelectTarget,	// ユーザー選択
			
			eState_End,
		};

		MonsterUnit* mMoveMonster;

	public:

		BattleProcCommand() :BtlTaskBase(),
		mMoveMonster(nullptr){}
		BattleProcCommand(MonsterUnit* moveMonster) :BtlTaskBase(),
			mMoveMonster(moveMonster) {
			BtlGetInfo().GetMoveData().Attacker = moveMonster;
		}

		bool Updata() override;
		void Draw()override;

		// 行動タイプを確認
		void _StateCheck();
		// 自動選択
		void _StateAutoTarget();
		// コマンド選択
		void _StateSelectCommand();
		// ユーザー選択
		void _StateSelectTarget();

	};

}


#endif // __BATTLE_PROC_COMMAND_H__