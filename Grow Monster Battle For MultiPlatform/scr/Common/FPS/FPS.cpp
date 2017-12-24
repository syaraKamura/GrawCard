/*
				ファイル名		:FPS.cpp
				作成者			:
				作成日時		:2017/12/19
				ソース説明		:
					
					FPS計測クラス
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "FPS.h"


/*
	コンストラクタ
	int sampleRate	:サンプルの数を設定
*/
FPS::FPS(int sampleRate,int fpsRate){

	mSampleReate = sampleRate;

	mNowTime = DxLib::GetNowCount();
	mOldTime = 0;
	mCounter = 0;

	mFpsRate = fpsRate;
	

	mFps = 0.0f;

	mOldDeltaTime = (float)DxLib::GetNowCount();
	mNowDeltaTime = 0.0f;
	mDeltaTime = 0.0f;

}

FPS::~FPS() {

}

void FPS::Updata() {

	if (mCounter == 0) {
		mOldTime = GetNowCount();
	}
	
	if(mCounter == mSampleReate){
		
		mNowTime = GetNowCount();

		mFps = 1000.0f / ((mNowTime - mOldTime) / (float)mSampleReate);
		mCounter = 0;
		mOldTime = mNowTime;
		
	}

	deltaTimeCalc();

	mCounter++;
}

void FPS::Wait() {

	int tookTime = GetNowCount() - mOldTime;
	int waitTime = mCounter * 1000 / mFpsRate - tookTime;
	if (waitTime > 0) {
		DxLib::WaitTimer(waitTime);	//待機
	}

}

void FPS::deltaTimeCalc() {
	
	mNowDeltaTime = GetNowCount();
	mDeltaTime = 1000.0f / (mNowDeltaTime - mOldDeltaTime) / mFpsRate;
	mOldDeltaTime = mNowDeltaTime;
}

void FPS::Draw() {

#ifdef  __MY_DEBUG__
	DrawFormatString(0, WINDOW_HEIGHT - 20, GetColor(255, 255, 255), "FPS:%0.1f delta:%f", mFps,mDeltaTime);
#endif //  __MY_DEBUG__


}

/*
	デルタタイムを返却する
*/
float FPS::GetDeltaTime() {
	return mDeltaTime;
}
