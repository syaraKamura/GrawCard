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


	class BtlInfo {

	private:

		int mTurn;
		std::vector<MonsterUnit*> mMonsterList;
		std::vector<MonsterUnit*> mPlayer;
		std::vector<MonsterUnit*> mEnemy;

		BATTLE_MOVE_DATA mMoveData{};

		int mMonsterNum[eSide_Max];

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

	};


}// battle


#endif // __BTL_INFO_H__