/*
				ファイル名		:FPS.h
				作成者			:
				作成日時		:2017/12/19
				ソース説明		:
					
					FPS計測クラス
				
				備考
					GameMgrに持たせる
				
				
!*/

#ifndef __FPS_H__
#define __FPS_H__

class FPS {

private:

	int mNowTime;
	int mOldTime;
	
	int mSampleReate;	//平均をとるサンプル数
	int mFpsRate;		//FPSを設定
	int mCounter;
	
	float mFps;

	float mOldDeltaTime;
	float mNowDeltaTime;
	float mDeltaTime;


public:

	/*
	コンストラクタ
	int sampleRate	:サンプルの数を設定
	int fpsrate		:目標のFPS(設定がなければ60FPSに設定)
	*/
	FPS(int sampleRate,int fpsRate = 60);
	
	/*
		デストラクタ
	*/
	~FPS();

	void Updata();
	
	

	/*
		待ち時間
	*/
	void Wait();

	void Draw();

	/*
		デルタタイムを返却する
	*/
	float GetDeltaTime();

private:

	/*
	デルタタイム計算
	*/
	void deltaTimeCalc();

};

#endif // __FPS_H__