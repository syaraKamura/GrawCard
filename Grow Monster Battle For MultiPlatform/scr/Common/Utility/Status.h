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

	public:

		Status() : mState(-1), mCounter(-1) {}

		bool IsEnd(int state);
		bool IsFirstState();

		void SetState(int state);
		int  GetState();

		void Update();

	};

}


#endif // __STATUS_H__