/*
				ファイル名		:Status.h
				作成者			:
				作成日時		:2019/06/09
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __STATUS_H__
#define __STATUS_H__

namespace Utility {

	class Status {

	private:

		int mCounter;
		int mState;
		int mNextState;
		int mOldState;
	public:

		Status() : mState(0), mNextState(-1), mOldState(-1),mCounter(0) {}
		Status(int state) : mState(state), mNextState(-1), mCounter(0) {}

		bool IsEnd(int state);
		bool IsFirstState();

		void SetState(int state);
		int  GetState();
		int GetOldState();

		void Update();

	};

}


#endif // __STATUS_H__