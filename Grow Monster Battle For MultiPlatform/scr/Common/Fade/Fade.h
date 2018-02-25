/*
				ファイル名		:Fade.h
				作成者			:
				作成日時		:2017/12/05
				ソース説明		:フェードクラス

				
				
				備考
					ゲーム起動時に生成しゲーム終了時に破棄をする
				
				
!*/

#ifndef __FADE_H__
#define __FADE_H__

#include "Common/Task/TaskBase.h"

const float FADE_VALUE_MAX = 255.0f;

class Fade:public TaskBase{

private:

	unsigned int mColor;	//色
	bool mIsFadeIn;			//フェードフラグ true:フェード中 false:フェード中ではない
	bool mIsFadeOut;		//フェードフラグ true:フェード中 false:フェード中ではない
	bool mIsFadeEnd;		//フェード終了フラグ

	float mFadeValue;		//フェードの値
	int mCounter;			//フェードカウンター

	int mFadeTime;			//フェードにかかる時間

private:

	Fade();

public :

	static Fade* GetInstance(){
		static Fade* inst = NULL;
		if(inst == NULL){
			inst = new Fade();
		}
		return inst;
	}

	
	~Fade();

	//色を設定する
	void SetFadeColor(unsigned int red,unsigned int green,unsigned int blue);
		
	void FadeIn(int fadeTime = 60);
	void FadeOut(int fadeTime = 60);

	bool IsFadeEnd();

	bool Initialize() override;
	void Finalize() override;
	bool Updata() override;
	void Draw() override;

};


#endif	//__FADE_H__