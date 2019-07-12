/*
				ファイル名		:BtlPhaseStart.h
				作成者			:
				作成日時		:2019/06/29
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __BTL_PHASE_START_H__
#define __BTL_PHASE_START_H__

#include "BtlTaskBase.h"
#include <vector>


namespace battle {

	class BattleBase;

	class BtlPhaseStart : public BtlTaskBase {

	private:

		enum eState {
			eState_Start,
			eState_Exit,
		};

		std::vector<MONSTER_DATA_t> mMonsterList;
		std::vector<int> mPlayerMonsterList;
		int mStartAnimCount;
		int mAnimPlayMonsterNum;
		

	public:
		
		BtlPhaseStart() : BtlTaskBase() ,
			mStartAnimCount(0),
			mAnimPlayMonsterNum(0){}

		BtlPhaseStart(std::vector<MONSTER_DATA_t>& pBase) : BtlTaskBase(), mMonsterList(pBase){
			mStartAnimCount = 0;
			mAnimPlayMonsterNum = 0;
		}

		bool Updata() override;

		void _StateInit();


	};

}

#endif // __BTL_PHASE_START_H__