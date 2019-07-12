/*
				ファイル名		:BtlTaskBase.h
				作成者			:
				作成日時		:2019/06/29
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __BTL_RASK_BASE_H__
#define __BTL_RASK_BASE_H__

#include "Common/Task/TaskBase.h"
#include "Common/Utility/Status.h"

#include "../BattleMgr.h"

namespace battle {

	class BtlTaskBase : public TaskBase {

	protected:

		Utility::Status mStatus;

	public:
		
		BtlTaskBase() : TaskBase(){}

		bool Updata() override { return true; }
		void Draw()override {}

	};

}

#endif // __BTL_RASK_BASE_H__