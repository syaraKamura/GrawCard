/*
				ファイル名		:BtlInfo.h
				作成者			:
				作成日時		:2019/07/06
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __BTL_INFO_H__
#define __BTL_INFO_H__

#include "../MonsterUnit/MonsterUnit.h"
#include <vector>

namespace battle {

	enum eBattleResult {
		eBattleResult_None,	// なし
		eBattleResult_Lose,	// 負け
		eBattleResult_Draw,	// 引き分け
		eBattleResult_Win,	// 勝ち
	};

	class BtlInfo {

	private:

		int mTurn;
		std::vector<MonsterUnit*> mMonsterList;
		std::vector<MonsterUnit*> mPlayer;
		std::vector<MonsterUnit*> mEnemy;

		BATTLE_MOVE_DATA mMoveData{};

		int mMonsterNum[eSide_Max];

		ePlayMode mPlayMode;

		eBattleResult mBattleResult;

	public:

		BtlInfo();
		~BtlInfo();

		void ClearData();

		int GetNowTurn() {
			return mTurn;
		}
		void AddTrun() {
			mTurn++;
		}
		
		// プレイモードを変える
		void ChangePlayMode() {
			mPlayMode = (mPlayMode == ePlayMode_Input) ? ePlayMode_Auto : ePlayMode_Input;
		}

		// 現在のプレイモードを取得する
		ePlayMode GetPlayMode() {
			return mPlayMode;
		}
		
		// プレイモードを設定する
		void SetPlayMode(ePlayMode mode) {
			mPlayMode = mode;
		}

		// プレイモードを確認する
		bool CheckPlayMode(ePlayMode mode) {
			return (mPlayMode == mode);
		}

		void AddMonster(MonsterUnit* monster);

		std::vector<MonsterUnit*>& GetMonsterList() {
			return mMonsterList;
		}

		std::vector<MonsterUnit*>& GetPlayerMonsterList() {
			return mPlayer;
		}
		std::vector<MonsterUnit*>& GetEnmeyMonsterList() {
			return mEnemy;
		}

		/*
			所持しているモンスターがすべて倒されているか？
		*/
		bool AllDeadMonster(eSide side);
		/*
			モンスターの所持数
		*/
		int GetHaveMonsterNum(eSide side) {
			return mMonsterNum[side];
		}

		BATTLE_MOVE_DATA& GetMoveData() {
			return mMoveData;
		};

		/*
			バトルの結果を設定する
		*/
		void BattleResult(eBattleResult Ret) {
			mBattleResult = Ret;
		}

		/*
			バトルの結果を返却する
		*/
		eBattleResult GetBattleResult() {
			return mBattleResult;
		}


	};


}// battle


#endif // __BTL_INFO_H__