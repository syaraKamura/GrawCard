/*
				ファイル名		:Button.cpp
				作成者			:
				作成日時		:2018/11/05
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "Common/System/OnListener.h"
#include "Common/ResourceTable/GraphTable.h"
#include "Common/String/StringBase.h"
#include "Common/String/FontMgr/BMFont.h"
#include "Button.h"


Button::Button(int posX, int posY, int width, int height, const char* str) : mLinstener(NULL), mGraph(NULL){

	mPosX = posX;
	mPosY = posY;
	mWidth = width;
	mHeight = height;

#ifdef __WINDOWS__
	strcpy_s(mStr, str);
#else
	strcpyDx(mStr, str);
#endif
	
	mIsPressed = false;
	mIsVisible = true;

	
	mString = new StringBase();
	mString->FontCreate("ＭＳ ゴシック",16,1,DX_FONTTYPE_NORMAL,GetColor(0,0,0));
	mString->SetString(str);
	mString->SetColor(GetColor(0, 0, 0));

	mAlpha = 255.0f;

}

Button::Button(const char* fileName, int posX, int posY, const char* str) : mLinstener(NULL) {
	
	mGraph = new Graphics();
	mGraph->Load(fileName);

	mGraph->GetSize(&mWidth, &mHeight);
	mGraph->SetPosition(posX, posY);

	mPosX = posX;
	mPosY = posY;

#ifdef __WINDOWS__
	strcpy_s(mStr, str);
#else
	strcpyDx(mStr, str);
#endif

	mIsPressed = false;
	mIsVisible = true;

	mString = new StringBase();
	mString->FontCreate("ＭＳ ゴシック", 16, 1, DX_FONTTYPE_NORMAL, GetColor(0, 0, 0));
	mString->SetString(str);
	mString->SetColor(GetColor(0, 0, 0));

	mAlpha = 255.0f;

}

Button::Button(int graphicsTag, int posX, int posY, const char* str) : mLinstener(NULL) {

	mGraph = new Graphics();
	//mGraph->Load(fileName);
	mGraph->Initialize(graphicsTable::GetGraphTag(graphicsTag));

	mGraph->GetSize(&mWidth, &mHeight);
	mGraph->SetPosition(posX, posY);
	mPosX = posX;
	mPosY = posY;


#ifdef __WINDOWS__
	strcpy_s(mStr, str);
#else
	strcpyDx(mStr, str);
#endif

	mIsPressed = false;
	mIsVisible = true;

	mString = new StringBase();
	mString->FontCreate("ＭＳ ゴシック", 16, 1, DX_FONTTYPE_NORMAL, GetColor(0, 0, 0));
	mString->SetString(str);
	mString->SetColor(GetColor(0,0,0));

	mAlpha = 255.0f;

}

Button::~Button() {

	if (mGraph != NULL) {
		mGraph->Relese();
		Delete(mGraph);
	}
	
	Delete(mString);

}

bool Button::Update() {

	if (mIsVisible == false) return true;

	int posX = ClickInput::GetInstance()->GetPositionX(0);
	int posY = ClickInput::GetInstance()->GetPositionY(0);

	int width = mPosX + mWidth;
	int height = mPosY + mHeight;

	if (mGraph != NULL) {
		mGraph->SetPosition(mPosX, mPosY);
	}

	mIsPressed = false;

	if (ClickInput::GetInstance()->Press(0)) {
		if ((posX >= mPosX && posX <= width) &&
			(posY >= mPosY && posY <= height)) {
			mIsPressed = true;
			if (mLinstener != NULL) {
				mLinstener->OnClick(this);
			}
		}
	}

	
	return true;
}

void Button::Draw() {

	if (mIsVisible == false) return;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, mAlpha);
	if (mGraph != nullptr) {
		mAlpha = 255;
		if (mIsPressed) {
			mAlpha = 123;
		}
		mGraph->SetAlpha(mAlpha);
		mGraph->Draw();


	}
	else {

		int sub = 0;
		if (mIsPressed) {
			sub = 2;
		}

		int posX = mPosX + sub;
		int posY = mPosY + sub;
		int width = mPosX + mWidth - sub;
		int height = mPosY + mHeight - sub;

		// ボタン用ボックス描画
		DrawBox(posX, posY, width, height, GetColor(100, 255, 255), TRUE);
		DrawBox(posX, posY, width, height, GetColor(255, 255, 255), FALSE);
		
	}
	
	int strWidth = GetDrawStringWidth(mStr, strlen(mStr));
	int strX = mPosX + mWidth / 2 - strWidth / 2;
	int strY = mPosY + mHeight / 2 - GetFontSize() / 2;

	// 文字列描画
	//DrawString(strX, strY, mStr, GetColor(0, 0, 0));
	mString->DrawString(strX,strY,(int)mAlpha);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Button::SetPosition(int posX, int posY) {

	if (mGraph != NULL) {
		mGraph->SetPosition(posX, posY);
	}
	mPosX = posX;
	mPosY = posY;

}

void Button::SetOnListener(OnListener* listener) {
	mLinstener = listener;
}

void Button::SetVisible(bool visible) {
	mIsVisible = visible;
}

bool Button::IsVisible() {
	return mIsVisible;
}

int Button::GetPositionX() {
	return mPosX;
}

int Button::GetPositionY() {
	return mPosY;
}

float Button::GetAlpha() {
	return mAlpha;
}

void Button::SetAlpha(float alpha) {
	mAlpha = alpha;
}