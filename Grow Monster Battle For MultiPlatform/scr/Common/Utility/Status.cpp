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
		return mCounter == 1;
	}

	void Status::SetState(int state) {	
		mNextState = state;
	}

	int Status::GetState() {
		return mState;
	}

	int Status::GetOldState() {
		return mOldState;
	}

	void Status::Update() {
		if (mNextState != -1) {
			mOldState = mState;
			mState = mNextState;
			mNextState = -1;
			mCounter = 0;
		}
		mCounter++;
	}

}


