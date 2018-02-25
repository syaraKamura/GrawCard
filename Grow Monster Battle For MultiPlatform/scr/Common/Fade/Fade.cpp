/*
				ファイル名		:Fade.h
				作成者			:
				作成日時		:2017/12/05
				ソース説明		:フェードクラス

				
				
				備考
					ゲーム起動時に生成しゲーム終了時に破棄をする
				
				
!*/

#include "DxLib.h"
#include "Fade.h"


Fade::Fade() : TaskBase(){
		
	mIsFadeEnd = true;
	mIsFadeIn = false;
	mIsFadeOut = false;
	mColor = GetColor(0,0,0);
	
	mFadeValue = 0.0f;
	mFadeTime = 60;
	mCounter = 0;

	mIsInitalize = true;
}

Fade::~Fade(){

}

void Fade::SetFadeColor(unsigned int red,unsigned int green,unsigned int blue){
	mColor = GetColor(red,green,blue);
}

void Fade::FadeIn(int fadeTime){
	mIsFadeIn = true;
	mIsFadeEnd = false;
	mFadeTime = fadeTime;
	mCounter = 0;
}

void Fade::FadeOut(int fadeTime){
	mIsFadeOut = true;
	mIsFadeEnd = false;
	mFadeTime = fadeTime;
	mCounter = 0;
}

bool Fade::IsFadeEnd(){
	return mIsFadeEnd;
}


bool Fade::Initialize(){

	
	return true;
}
void Fade::Finalize(){}

bool Fade::Updata(){

	if(mIsFadeEnd == true) return true;

	if(mIsFadeIn == true && mIsFadeEnd == false){
		mFadeValue = 255.0f - 255.0f * (float)(mCounter) / (float)(mFadeTime);
		
		if(mFadeValue < 0){
			mFadeValue = 0;
		}

		if(mCounter >= mFadeTime){
			mIsFadeEnd = true;
			mIsFadeIn = false;
		}


	}else if (mIsFadeOut == true && mIsFadeIn == false){
		mFadeValue = 255.0f * (float)(mCounter) / (float)(mFadeTime);

		if(mFadeValue > FADE_VALUE_MAX){
			mFadeValue = FADE_VALUE_MAX;
		}

		if(mCounter >= mFadeTime){
			mIsFadeEnd = true;
			mIsFadeOut = false;
		}

	}

	mCounter++;
	
	return true;
}

void Fade::Draw(){

	//if(mIsFadeEnd == true) return;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA,mFadeValue);
	DrawBox(0,0,900,800,mColor,TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);

}