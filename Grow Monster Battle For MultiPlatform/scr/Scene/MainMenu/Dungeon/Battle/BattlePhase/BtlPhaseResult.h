/*
				ファイル名		:BtlPhaseResult.h
				作成者			:
				作成日時		:2019/06/29
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __BTL_PHASE_RESULT_H__
#define __BTL_PHASE_RESULT_H__

#include "BtlTaskBase.h"

namespace battle {

	class BtlPhaseResult : public BtlTaskBase {

	private:

		enum eState {
			eState_Check,		// 状態を確認する
			eState_Succeed,		// 成功
			eState_Failed,		// 失敗
			eState_End,
		};

	public:

		BtlPhaseResult() {};
		~BtlPhaseResult() {};

		void Draw() override{}
		bool Updata() override;

		// 状態を確認する
		void _StateCheck();
		// 成功
		void _StateSucceed();
		// 失敗
		void _StateFailed();

	};

}


#endif // __BTL_PHASE_RESULT_H__