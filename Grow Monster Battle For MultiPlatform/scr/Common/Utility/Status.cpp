/*
				ファイル名		:Status.cpp
				作成者			:
				作成日時		:2019/06/09
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Status.h"

namespace Utility {

	bool Status::IsEnd(int state) {
		return mState == state;
	}

	bool Status::IsFirstState() {
		return mCounter <= 0;
	}

	void Status::SetState(int state) {
		if (mState != state) {
			mCounter = -1;
			mState = state;
		}
	}

	int Status::GetState() {
		return mState;
	}

	void Status::Update() {
		mCounter++;
	}

}


